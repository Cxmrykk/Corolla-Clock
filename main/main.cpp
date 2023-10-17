

#include <Arduino.h>
#include <esp_timer.h>
#include <driver/gpio.h>

#include "rm67162.h"
#include "TFT_eSPI.h"
#include "main.h"

// extension board IO
#define GPIO_LAMP (gpio_num_t) 46
#define GPIO_ACC (gpio_num_t) 45
#define GPIO_RESET (gpio_num_t) 21
#define GPIO_HOUR (gpio_num_t) 43
#define GPIO_MINUTE (gpio_num_t) 42

// screen
#define SCREEN_X 536
#define SCREEN_Y 240

// canvas
#define CANVAS_X 510
#define CANVAS_Y 146

uint16_t offset[2] = { 0, 0 };
uint8_t brightness = 255;

// default state 0
gpio_state_t gpio_state = { 0, 0, 0, 0, 0 };

// starts at midnight
clock_state_t clock_state = {
    hour: 0,
    minute: 0,
    second: 0
};

uint8_t mode = 0;

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

void increment_timer() {
    clock_state.second++;
    // 60 seconds have passed
    if (clock_state.second >= 60) {
        clock_state.second = 0;
        clock_state.minute++;
        // 60 minutes have passed
        if (clock_state.minute >= 60) {
            clock_state.minute = 0;
            clock_state.hour++;
            // 24 hours have passed
            if (clock_state.hour >= 24) {
                clock_state.hour = 0;
            }
        }
    }
}

void setup() { 
    rm67162_init(); // amoled initialization
    lcd_setRotation(3);
    lcd_brightness(brightness);
    sprite.createSprite(SCREEN_X, SCREEN_Y);
    sprite.setSwapBytes(1);

    // set GPIO direction
    gpio_set_direction(GPIO_ACC, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_LAMP, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_RESET, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_HOUR, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_MINUTE, GPIO_MODE_INPUT);

    // car signals VCC
    gpio_set_pull_mode(GPIO_ACC, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GPIO_LAMP, GPIO_PULLDOWN_ONLY);

    // use external pull-up resistor for buttons by default
    gpio_set_pull_mode(GPIO_RESET, GPIO_FLOATING);
    gpio_set_pull_mode(GPIO_HOUR, GPIO_FLOATING);
    gpio_set_pull_mode(GPIO_MINUTE, GPIO_FLOATING);

    // initialise timer
    esp_timer_handle_t periodic_timer;
    const esp_timer_create_args_t periodic_timer_args = {
            .callback = (esp_timer_cb_t) &increment_timer,
            .name = "periodic"
    };
    esp_timer_create(&periodic_timer_args, &periodic_timer);
    esp_timer_start_periodic(periodic_timer, 1000000); // 1 second interval
}

void draw_handler() {
    sprite.fillSprite(TFT_BLACK);

    /*
        Display a border around the canvas if alignment is toggled
    */
    if (mode == 1 || mode == 2) {
        // possibly out of bounds
        sprite.fillRect(offset[0] - 1, offset[1] - 1, CANVAS_X + 2, CANVAS_Y + 2, TFT_RED);
    }
    sprite.fillRect(offset[0], offset[1], CANVAS_X, CANVAS_Y, TFT_BLACK);

    /*
        Display the current time as text
    */
    char current_time_str[20];
    sprintf(current_time_str, "Time: %02d:%02d:%02d", clock_state.hour, clock_state.minute, clock_state.second);
    sprite.drawString(current_time_str, offset[0] + 20, offset[1] + 20, 4);

    /*
        Display the mode as text at the bottom of the screen
    */
    switch (mode) {
        case 1:
            sprite.drawString("Set Horizontal Alignment", offset[0] + 20, (offset[1] + CANVAS_Y) - 40, 4);
            break;
        case 2:
            sprite.drawString("Set Vertical Alignment", offset[0] + 20, (offset[1] + CANVAS_Y) - 40, 4);
            break;
        case 3:
            sprite.drawString("Set Time", offset[0] + 20, (offset[1] + CANVAS_Y) - 40, 4);
            break;
        case 4:
            sprite.drawString("Set Brightness", offset[0] + 20, (offset[1] + CANVAS_Y) - 40, 4);
            break;
    }

    lcd_PushColors(0, 0, 536, 240, (uint16_t*)sprite.getPointer());
}

void gpio_handler() {
    // buttons pull high by default
    bool gpio_reset_active = !gpio_get_level(GPIO_RESET);
    bool gpio_hour_active = !gpio_get_level(GPIO_HOUR);
    bool gpio_min_active = !gpio_get_level(GPIO_MINUTE);

    bool gpio_reset = gpio_reset_active && !gpio_state.reset;
    bool gpio_hour = gpio_hour_active && !gpio_state.hour;
    bool gpio_minute = gpio_min_active && !gpio_state.minute;

    /*
        Toggle state on
    */
    if (gpio_reset) {
        gpio_state.reset = 1;
    }

    if (gpio_hour) {
        gpio_state.hour = 1;
    }

    if (gpio_minute) {
        gpio_state.minute = 1;
    }

    /*
        Toggle state off
    */
    if (!gpio_reset_active && gpio_state.reset) {
        gpio_state.reset = 0;
    }

    if (!gpio_hour_active && gpio_state.hour) {
        gpio_state.hour = 0;
    }

    if (!gpio_min_active && gpio_state.minute) {
        gpio_state.minute = 0;
    }

    /*
        Modes:
        0: Clock (off)
        1: Horizontal Alignment (left, right)
        2: Vertical Alignment (up, down)
        3: Set Time (hour, minute)
        4: Brightness (+, -)
    */
    switch (mode) {
        case 1:
            // horizontal left
            if (gpio_hour && offset[0] > 0) {
                offset[0]--;
            }
            // horizontal right
            if (gpio_minute && offset[0] < (SCREEN_X - CANVAS_X)) {
                offset[0]++;
            }
            break;
        case 2:
            // vertical up
            if (gpio_hour && offset[1] > 0) {
                offset[1]--;
            }
            // vertical down
            if (gpio_minute && offset[1] < (SCREEN_Y - CANVAS_Y)) {
                offset[1]++;
            }
            break;
        case 3:
            // increment hour
            if (gpio_hour) {
                clock_state.hour++;
                if (clock_state.hour >= 24) {
                    clock_state.hour = 0;
                }
                clock_state.second = 0;
            }
            // increment minute
            if (gpio_minute) {
                clock_state.minute++;
                if (clock_state.minute >= 60) {
                    clock_state.minute = 0;
                }
                clock_state.second = 0;
            }
            break;
        case 4:
            // brightness up
            if (gpio_hour_active && brightness < 255) {
                brightness++;
                lcd_brightness(brightness);
            }
            if (gpio_min_active && brightness > 55) {
                brightness--;
                lcd_brightness(brightness);
            }
            break;
    }

    /*
        Reset button (:00) toggles mode
    */
    if (gpio_reset) {
        mode++;
        // cycle back to mode 0
        if (mode > 4) {
            mode = 0;
        }
    }
}

void loop() {
    gpio_handler();
    draw_handler();
}
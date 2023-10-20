#include <Arduino.h>
#include <TFT_eSPI.h>
#include <esp_timer.h>
#include <driver/gpio.h>

#include "digital_clock.h"
#include "driver/rm67162.h"
#include "main.h"
#include "rgb565.h"

// initialise screen brightness
uint8_t brightness = MAX_BRIGHTNESS;

// foreground white & background black (maximum: 63)
uint8_t digit_whiteness = 0;
uint8_t digit_opacity = GREEN_MAXIMUM / 10;

// clock digit colours
color_t digit_hue = { 0, GREEN_MAXIMUM, 0 };
color_t digit_foreground = {0, GREEN_MAXIMUM, 0 };
color_t digit_background = { 0, GREEN_MAXIMUM / 10, 0 };

// whiteness/hue button direction
bool digit_whiteness_direction = 1;
//bool digit_hue_direction = 0;

// initialise gpio state tracker
gpio_state_t gpio_state = { 0, 0, 0, 0, 0 };
gpio_state_t gpio_active = { 0, 0, 0, 0, 0 };
gpio_hold_state_t gpio_hold_state = { 0, 0, 0, 0, 0 };

// initialise clock
clock_state_t clock_state = {
    .hour = 0,
    .minute = 0,
    .second = 0
};

digital_clock_t digital_clock = {
    &clock_state,
    &digit_foreground,
    &digit_background,
    DIGIT_PADDING,
    DIGIT_WIDTH,
    DIGIT_THICKNESS
};

// canvas offset
uint16_t offset[2] = { 0, 0 };

// clock offset (centered)
uint16_t const clock_offset[2] = {
    (uint16_t) ((CANVAS_X - clock_width(&digital_clock)) / 2),
    (uint16_t) ((CANVAS_Y - clock_height(&digital_clock)) / 2)
};

// clock mode
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

    // buttons 3.3V
    gpio_set_pull_mode(GPIO_RESET, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GPIO_HOUR, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GPIO_MINUTE, GPIO_PULLDOWN_ONLY);

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
        sprite.drawRect(offset[0] - 1, offset[1] - 1, CANVAS_X + 2, CANVAS_Y + 2, TFT_RED);
    }
    //sprite.fillRect(offset[0], offset[1], CANVAS_X, CANVAS_Y, TFT_BLACK);

    /*
        Draw the clock
    */
    draw_digital_clock(&sprite, &digital_clock, clock_offset[0] + offset[0], clock_offset[1] + offset[1]);

    /*
        Display the mode as text at the bottom of the screen
    */
    switch (mode) {
        case 1:
            sprite.drawString("Set Horizontal Alignment", offset[0], offset[1], 4);
            sprite.drawString("H: Move display left", offset[0], offset[1] + 26, 4);
            sprite.drawString("M: Move display right", offset[0], offset[1] + 52, 4);
            break;
        case 2:
            sprite.drawString("Set Vertical Alignment", offset[0], offset[1], 4);
            sprite.drawString("H: Move display up", offset[0], offset[1] + 26, 4);
            sprite.drawString("M: Move display down", offset[0], offset[1] + 52, 4);
            break;
        case 3:
            sprite.drawString("Set Time", offset[0], offset[1], 4);
            sprite.drawString("H: Set hour", offset[0], offset[1] + 26, 4);
            sprite.drawString("M: Set minute", offset[0], offset[1] + 52, 4);
            break;
        case 4:
            sprite.drawString("Set Brightness", offset[0], offset[1], 4);
            sprite.drawString("H: Increase brightness", offset[0], offset[1] + 26, 4);
            sprite.drawString("M: Decrease brightness", offset[0], offset[1] + 52, 4);
            break;
        case 5:
            sprite.drawString("Set Colour", offset[0], offset[1], 4);
            sprite.drawString("H: Set Hue", offset[0], offset[1] + 26, 4);
            sprite.drawString("M: Set Brightness", offset[0], offset[1] + 52, 4);
            break;
        case 6:
            sprite.drawString("Set Opacity", offset[0], offset[1], 4);
            sprite.drawString("H: Increase Opacity", offset[0], offset[1] + 26, 4);
            sprite.drawString("M: Decrease Opacity", offset[0], offset[1] + 52, 4);
            break;
    }

    lcd_PushColors(0, 0, SCREEN_X, SCREEN_Y, (uint16_t*) sprite.getPointer());
}

void gpio_handler() {
    // get actual GPIO high/low state
    gpio_active.reset = !gpio_get_level(GPIO_RESET);
    gpio_active.hour = !gpio_get_level(GPIO_HOUR);
    gpio_active.minute = !gpio_get_level(GPIO_MINUTE);

    // get interpreted GPIO high/low state (button held for cycle duration)
    bool gpio_reset_active = gpio_active.reset && gpio_hold_state.reset == GPIO_HOLD_COUNT;
    bool gpio_hour_active = gpio_active.hour && gpio_hold_state.hour == GPIO_HOLD_COUNT;
    bool gpio_min_active =  gpio_active.minute && gpio_hold_state.minute == GPIO_HOLD_COUNT;

    // get toggled GPIO high/low state
    bool gpio_reset = gpio_reset_active && !gpio_state.reset;
    bool gpio_hour = gpio_hour_active && !gpio_state.hour;
    bool gpio_minute = gpio_min_active && !gpio_state.minute;

    /*
        Update GPIO hold state
    */
    if (gpio_active.reset && gpio_hold_state.reset < GPIO_HOLD_COUNT) {
        gpio_hold_state.reset++;
    } else

    if (!gpio_active.reset && gpio_hold_state.reset > 0) {
        gpio_hold_state.reset--;
    }

    if (gpio_active.hour && gpio_hold_state.hour < GPIO_HOLD_COUNT) {
        gpio_hold_state.hour++;
    } else

    if (!gpio_active.hour && gpio_hold_state.hour > 0) {
        gpio_hold_state.hour--;
    }

    if (gpio_active.minute && gpio_hold_state.minute < GPIO_HOLD_COUNT) {
        gpio_hold_state.minute++;
    } else

    if (!gpio_active.minute && gpio_hold_state.minute > 0) {
        gpio_hold_state.minute--;
    }

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
        5: Colour (hue, brightness)
        6: Opacity (+, -)
    */
    switch (mode) {
        case 1:
            // horizontal left
            if (gpio_hour_active && offset[0] > 0) {
                offset[0]--;
            }
            // horizontal right
            if (gpio_min_active && offset[0] < (SCREEN_X - CANVAS_X)) {
                offset[0]++;
            }
            break;

        case 2:
            // vertical up
            if (gpio_hour_active && offset[1] > 0) {
                offset[1]--;
            }
            // vertical down
            if (gpio_min_active && offset[1] < (SCREEN_Y - CANVAS_Y)) {
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
            if (gpio_hour_active && brightness < MAX_BRIGHTNESS) {
                brightness++;
                lcd_brightness(brightness);
            }
            if (gpio_min_active && brightness > MIN_BRIGHTNESS) {
                brightness--;
                lcd_brightness(brightness);
            }
            break;

        case 5:
            if (gpio_hour_active) {
                increment_color(&digit_hue, false);
                update_colors(&digit_hue, &digit_foreground, &digit_background, digit_whiteness, digit_opacity);
            }

            if (gpio_min_active) {
                // toggle direction on button press
                if (gpio_minute) {
                    digit_whiteness_direction = !digit_whiteness_direction;
                }

                // increment whiteness value, update active colour
                if (digit_whiteness_direction && digit_whiteness < GREEN_MAXIMUM) {
                    digit_whiteness++;
                    update_colors(&digit_hue, &digit_foreground, &digit_background, digit_whiteness, digit_opacity);
                } else

                // decrement whiteness value, update active colour
                if (!digit_whiteness_direction && digit_whiteness > 0) {
                    digit_whiteness--;
                    update_colors(&digit_hue, &digit_foreground, &digit_background, digit_whiteness, digit_opacity);
                }
            }
            break;

        case 6:
            if (gpio_hour_active && digit_opacity < GREEN_MAXIMUM) {
                digit_opacity++;
                update_colors(&digit_hue, &digit_foreground, &digit_background, digit_whiteness, digit_opacity);
            }

            if (gpio_min_active && digit_opacity > 0) {
                digit_opacity--;
                update_colors(&digit_hue, &digit_foreground, &digit_background, digit_whiteness, digit_opacity);
            }
            break;
    }

    /*
        Reset button (:00) toggles mode
    */
    if (gpio_reset) {
        mode++;
        // cycle back to mode 0
        if (mode > 6) {
            mode = 0;
        }
    }
}

void loop() {
    sprite.setTextSize(1);
    gpio_handler();
    draw_handler();
}
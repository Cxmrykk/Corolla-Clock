#include <Arduino.h>
#include <TFT_eSPI.h>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>

#include "clock.h"
#include "drivers/rm67162.h"
#include "drivers/gpio_states.h"
#include "sprites/digital_clock.h"
#include "sprites/text_display.h"
#include "sprites/tools/rgb565.h"

Clock_State_t state = {
    // Lamp off clock colours
    .lamp_off_hue = { 0, GREEN_MAXIMUM, 0 },
    .lamp_off_foreground = {0, GREEN_MAXIMUM, 0 },
    .lamp_off_background = { 0, GREEN_MAXIMUM / 10, 0 },

    // Lamp on clock colours
    .lamp_on_hue = { RED_MAXIMUM, 0, 0 },
    .lamp_on_foreground = {RED_MAXIMUM, 0, 0 },
    .lamp_on_background = { RED_MAXIMUM / 10, 0, 0 },

    // Clock state
    .timer = {
        .hour = 0,
        .minute = 0,
        .second = 0
    },

    // Digital clock configurations for lamp on and off states
    .lamp_on_digital_clock = {
        &state.timer,
        &state.lamp_on_foreground,
        &state.lamp_on_background,
        DIGIT_PADDING,
        DIGIT_WIDTH,
        DIGIT_THICKNESS
    },

    .lamp_off_digital_clock = {
        &state.timer,
        &state.lamp_off_foreground,
        &state.lamp_off_background,
        DIGIT_PADDING,
        DIGIT_WIDTH,
        DIGIT_THICKNESS
    },

    // Clock profiles for lamp on and off states
    .lamp_on_profile = {
        &state.lamp_on_digital_clock,
        &state.lamp_on_hue,
        LAMP_ON_BRIGHTNESS,
        0,
        0
    },

    .lamp_off_profile = {
        &state.lamp_off_digital_clock,
        &state.lamp_off_hue,
        LAMP_OFF_BRIGHTNESS,
        0,
        0
    },

    // Current profile
    .profile = &state.lamp_off_profile,

    // Canvas offset
    .offset = { 0, 0 },

    // Clock offset (centered)
    .clock_offset = {
        (int16_t) ((CANVAS_X - clock_width(state.profile->digital_clock)) / 2),
        (int16_t) ((CANVAS_Y - clock_height(state.profile->digital_clock)) / 2)
    },

    // Timeout event (resets when accessory is on)
    .timeout = TIMEOUT_DURATION,

    // Button toggles
    .mode_toggle = 0,
    .lamp_toggle = 0,
    .screen_toggle = 0,
    .whiteness_toggle = 0,

    .time_updated = 0,

    // Current mode
    .mode = 0,

    .tft = TFT_eSPI(),
    .sprite = TFT_eSprite(&state.tft)
};

void timer() {
    state.timer.second++;
    state.time_updated = 1;
    
    // 60 seconds have passed
    if (state.timer.second >= 60) {
        state.timer.second = 0;
        state.timer.minute++;

        // 60 minutes have passed
        if (state.timer.minute >= 60) {
            state.timer.minute = 0;
            state.timer.hour++;

            // 24 hours have passed
            if (state.timer.hour >= 24) {
                state.timer.hour = 0;
            }
        }
    }
}

void setup() {
    rm67162_init(); // amoled initialization
    lcd_setRotation(3);
    state.sprite.createSprite(SCREEN_X, SCREEN_Y);
    state.sprite.setSwapBytes(1);

    // disconnect the pin from any other peripheral functions
    gpio_pad_select_gpio(GPIO_LAMP);
    gpio_pad_select_gpio(GPIO_ACC);
    gpio_pad_select_gpio(GPIO_RESET);
    gpio_pad_select_gpio(GPIO_HOUR);
    gpio_pad_select_gpio(GPIO_MINUTE);

    // set GPIO direction
    gpio_set_direction(GPIO_LAMP, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_ACC, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_RESET, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_HOUR, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_MINUTE, GPIO_MODE_INPUT);

    // set internal pulldown by default
    gpio_set_pull_mode(GPIO_LAMP, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GPIO_ACC, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GPIO_RESET, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GPIO_HOUR, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GPIO_MINUTE, GPIO_PULLDOWN_ONLY);

    // initialise timer
    esp_timer_handle_t periodic_timer;
    const esp_timer_create_args_t periodic_timer_args = {
            .callback = (esp_timer_cb_t) &timer,
            .name = "periodic"
    };
    esp_timer_create(&periodic_timer_args, &periodic_timer);
    esp_timer_start_periodic(periodic_timer, 1000000); // 1 second interval
}

void loop() {
    timeout_handler(&state);
    gpio_handler(&state);
    draw_handler(&state);
    vTaskDelay(1000 / REFRESH_RATE);
}
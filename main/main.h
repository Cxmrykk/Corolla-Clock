#ifndef MAIN_H
#define MAIN_H

    #include "digital_clock.h"

    // watchdog vTaskDelay (screen refresh rate in Hertz)
    #define REFRESH_RATE 60

    // screen
    #define SCREEN_X 536
    #define SCREEN_Y 240

    // canvas
    #define CANVAS_X 508
    #define CANVAS_Y 144

    // max/min screen brightness
    #define MAX_BRIGHTNESS 255
    #define MIN_BRIGHTNESS 55

    // default brightness
    #define LAMP_OFF_BRIGHTNESS 255
    #define LAMP_ON_BRIGHTNESS 155

    // digit colours RGB565
    #define DIGIT_COLOR_ACTIVE ((12 << 11) | (40 << 5) | 12)
    #define DIGIT_COLOR_INACTIVE ((4 << 11)  | (12 << 5) | 4)

    // digit dimensions (must be even number)
    #define DIGIT_PADDING 4
    #define DIGIT_WIDTH 64
    #define DIGIT_THICKNESS 12

    // timeout events
    #define TIMEOUT_DURATION 10
    #define TIMEOUT_BRIGHTNESS 5
    #define TIMEOUT_DISPLAY 1

    typedef struct {
        digital_clock_t *digital_clock;
        color_t *hue;
        uint8_t brightness;
        uint8_t whiteness;
        uint8_t opacity;
    } clock_profile_t;

#endif
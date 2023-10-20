#ifndef MAIN_H
#define MAIN_H

    // extension board IO
    #define GPIO_LAMP GPIO_NUM_46
    #define GPIO_ACC GPIO_NUM_45
    #define GPIO_RESET GPIO_NUM_44
    #define GPIO_HOUR GPIO_NUM_43
    #define GPIO_MINUTE GPIO_NUM_42

    // screen
    #define SCREEN_X 536
    #define SCREEN_Y 240

    // canvas
    #define CANVAS_X 510
    #define CANVAS_Y 146

    // max/min screen brightness
    #define MAX_BRIGHTNESS 255
    #define MIN_BRIGHTNESS 55

    // clock colon colour RGB565
    #define CLOCK_COLON_COLOR ((12 << 11) | (40 << 5) | 12)

    // digit colours RGB565
    #define DIGIT_COLOR_ACTIVE ((12 << 11) | (40 << 5) | 12)
    #define DIGIT_COLOR_INACTIVE ((4 << 11)  | (12 << 5) | 4)

    // digit dimensions (must be even number)
    #define DIGIT_PADDING 4
    #define DIGIT_WIDTH 64
    #define DIGIT_THICKNESS 12

    // maximum loop cycles to register GPIO event (prevents noise causing faulty inputs)
    #define GPIO_HOLD_COUNT 5

    typedef struct {
        bool accessory;
        bool lamp;
        bool reset;
        bool hour;
        bool minute;
    } gpio_state_t;

    typedef struct {
        uint8_t accessory;
        uint8_t lamp;
        uint8_t reset;
        uint8_t hour;
        uint8_t minute;
    } gpio_hold_state_t;

    typedef struct {
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
    } clock_state_t;

#endif
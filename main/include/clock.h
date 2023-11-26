#ifndef CLOCK_H
#define CLOCK_H

    #include "drivers/rm67162.h"
    #include "drivers/gpio_states.h"
    #include "sprites/digital_clock.h"
    #include "sprites/text_display.h"
    #include "sprites/tools/rgb565.h"

    // watchdog vTaskDelay (screen refresh rate in Hertz)
    #define REFRESH_RATE 60

    // screen
    #define SCREEN_X 536
    #define SCREEN_Y 240

    // canvas
    #define CANVAS_X 508
    #define CANVAS_Y 142

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
    #define DIGIT_WIDTH 58
    #define DIGIT_THICKNESS 10

    // timeout events
    #define TIMEOUT_DURATION 10
    #define TIMEOUT_BRIGHTNESS 5
    #define TIMEOUT_DISPLAY 1

    typedef struct {
        Clock_Sprite_t *digital_clock;
        Color_t *hue;
        uint8_t brightness;
        uint8_t whiteness;
        uint8_t opacity;
    } Clock_Profile_t;

    typedef struct {
        // Lamp off clock colours
        Color_t lamp_off_hue;
        Color_t lamp_off_foreground;
        Color_t lamp_off_background;

        // Lamp on clock colours
        Color_t lamp_on_hue;
        Color_t lamp_on_foreground;
        Color_t lamp_on_background;

        // Clock state
        Timer_State_t timer;

        // Digital clock configurations for lamp on and off states
        Clock_Sprite_t lamp_on_digital_clock;
        Clock_Sprite_t lamp_off_digital_clock;

        // Clock profiles for lamp on and off states
        Clock_Profile_t lamp_on_profile;
        Clock_Profile_t lamp_off_profile;

        // Current profile
        Clock_Profile_t* profile;

        // Canvas offset
        int16_t offset[2];

        // Clock offset (centered)
        int16_t clock_offset[2];

        // Timeout event (resets when accessory is on)
        uint8_t timeout;

        // Button toggles
        bool mode_toggle;
        bool lamp_toggle;
        bool screen_toggle;
        bool whiteness_toggle;

        // Flag to check if time is updated
        bool time_updated;

        // Current mode
        uint8_t mode;

        // TFT display and sprite
        TFT_eSPI tft;
        TFT_eSprite sprite;
    } Clock_State_t;

    void update_clock_offset(Clock_State_t *state);
    void timeout_handler(Clock_State_t *state);
    void draw_handler(Clock_State_t *state);
    void gpio_handler(Clock_State_t *state);

#endif
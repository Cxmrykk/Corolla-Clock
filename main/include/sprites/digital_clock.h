#ifndef DIGITAL_CLOCK_H
#define DIGITAL_CLOCK_H

    #include "sprites/digital_num.h"
    #include "sprites/tools/rgb565.h"

    typedef struct {
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
    } Timer_State_t;

    typedef struct {
        Timer_State_t *timer;
        Color_t *color_active;
        Color_t *color_inactive;
        uint16_t padding;
        uint16_t width;
        uint16_t thickness;
    } Clock_Sprite_t;

    uint16_t clock_height(Clock_Sprite_t *digital_clock);
    uint16_t clock_width(Clock_Sprite_t *digital_clock);
    void draw_digital_clock(TFT_eSprite *sprite, Clock_Sprite_t *digital_clock, uint16_t x, uint16_t y);

#endif
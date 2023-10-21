#ifndef DIGITAL_CLOCK_H
#define DIGITAL_CLOCK_H

    #include "digital_num.h"
    #include "rgb565.h"

    typedef struct {
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
    } clock_state_t;

    typedef struct {
        clock_state_t *clock_state;
        color_t *color_active;
        color_t *color_inactive;
        uint16_t padding;
        uint16_t width;
        uint16_t thickness;
    } digital_clock_t;

    uint16_t clock_height(digital_clock_t *digital_clock);
    uint16_t clock_width(digital_clock_t *digital_clock);
    void draw_digital_clock(TFT_eSprite *sprite, digital_clock_t *digital_clock, uint16_t x, uint16_t y);

#endif
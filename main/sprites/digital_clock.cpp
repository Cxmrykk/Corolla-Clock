#include <TFT_eSPI.h>
#include "digital_clock.h"
#include "rgb565.h"
#include "main.h"

uint16_t clock_height(digital_clock_t *digital_clock) {
    return (4 * digital_clock->padding) + (3 * digital_clock->thickness) + (2 * (digital_clock->width - (2 * digital_clock->padding) - (2 * digital_clock->thickness)));
}

uint16_t clock_width(digital_clock_t *digital_clock) {
    return (14 * digital_clock->padding) + (6 * digital_clock->width) + (2 * digital_clock->thickness);
}

void draw_digital_clock(TFT_eSprite *sprite, digital_clock_t *digital_clock, uint16_t x, uint16_t y) {
    uint16_t digit_height = clock_height(digital_clock);

    // convert colours to rgb565 integer
    uint16_t color_active = to_rgb565(digital_clock->color_active);
    uint16_t color_inactive = to_rgb565(digital_clock->color_inactive);

    // easier to read
    uint8_t hour = digital_clock->clock_state->hour;
    uint8_t minute = digital_clock->clock_state->minute;
    uint8_t second = digital_clock->clock_state->second;

    // get value of each digit
    uint8_t hour_digits[2] = { (uint8_t) (hour / 10), (uint8_t) (hour - ((hour / 10) * 10)) };
    uint8_t minute_digits[2] = { (uint8_t) (minute / 10), (uint8_t) (minute - ((minute / 10) * 10)) };
    uint8_t second_digits[2] = { (uint8_t) (second / 10), (uint8_t) (second - ((second / 10) * 10)) };

    // initialise digital number
    digital_num_t digital_num = {
        digital_clock->thickness,
        digital_clock->padding,
        digital_clock->width,
        color_active,
        color_inactive,
        active_segments(hour_digits[0])
    };

    // draw hour digits, update segments for next digits
    draw_digital_num(sprite, &digital_num, x, y);
    digital_num.active = active_segments(hour_digits[1]);
    x += digital_clock->width + (digital_clock->padding * 2);

    draw_digital_num(sprite, &digital_num, x, y);
    digital_num.active = active_segments(minute_digits[0]);
    x += digital_clock->width + (digital_clock->padding * 2);

    // draw colon separating hour and minute digits
    sprite->fillRect(x, y + (digit_height / 2) - (digit_height / 4) - (digital_clock->thickness / 2),
        digital_clock->thickness, digital_clock->thickness,
        color_active);

    sprite->fillRect(x, y + (digit_height / 2) + (digit_height / 4) - (digital_clock->thickness / 2),
        digital_clock->thickness, digital_clock->thickness,
        color_active);

    x += digital_clock->thickness + (digital_clock->padding * 2);

    // draw minute digits, update segments for next digits
    draw_digital_num(sprite, &digital_num, x, y);
    digital_num.active = active_segments(minute_digits[1]);
    x += digital_clock->width + (digital_clock->padding * 2);

    draw_digital_num(sprite, &digital_num, x, y);
    digital_num.active = active_segments(second_digits[0]);
    x += digital_clock->width + (digital_clock->padding * 2);

    // draw colon separating minute and second digits
    sprite->fillRect(x, y + (digit_height / 2) - (digit_height / 4) - (digital_clock->thickness / 2),
        digital_clock->thickness, digital_clock->thickness,
        color_active);

    sprite->fillRect(x, y + (digit_height / 2) + (digit_height / 4) - (digital_clock->thickness / 2),
        digital_clock->thickness, digital_clock->thickness,
        color_active);

    x += digital_clock->thickness + (digital_clock->padding * 2);

    // draw second digits
    draw_digital_num(sprite, &digital_num, x, y);
    digital_num.active = active_segments(second_digits[1]);
    x += digital_clock->width + (digital_clock->padding * 2);

    draw_digital_num(sprite, &digital_num, x, y);
}
#include <TFT_eSPI.h>
#include "digital_clock.h"

uint16_t clock_height() {
    return (4 * DIGIT_PADDING) + (3 * DIGIT_THICKNESS) + (2 * (DIGIT_WIDTH - (2 * DIGIT_PADDING) - (2 * DIGIT_THICKNESS)));
}

uint16_t clock_width() {
    return (14 * DIGIT_PADDING) + (6 * DIGIT_WIDTH) + (2 * DIGIT_THICKNESS);
}

void draw_digital_clock(TFT_eSprite *sprite, uint16_t x, uint16_t y, uint8_t hour, uint8_t minute, uint8_t second) {
    uint16_t digit_height = clock_height();

    // get value of each digit
    uint8_t hour_digits[2] = { (uint8_t) (hour / 10), (uint8_t) (hour - ((hour / 10) * 10)) };
    uint8_t minute_digits[2] = { (uint8_t) (minute / 10), (uint8_t) (minute - ((minute / 10) * 10)) };
    uint8_t second_digits[2] = { (uint8_t) (second / 10), (uint8_t) (second - ((second / 10) * 10)) };

    // initialise digital number
    digital_num_t digital_num = {
        DIGIT_THICKNESS,
        DIGIT_PADDING,
        DIGIT_WIDTH,
        DIGIT_COLOR_ACTIVE,
        DIGIT_COLOR_INACTIVE,
        active_segments(hour_digits[0])
    };

    // draw hour digits, update segments for next digits
    draw_digital_num(sprite, &digital_num, x, y);
    digital_num.active = active_segments(hour_digits[1]);
    x += DIGIT_WIDTH + (DIGIT_PADDING * 2);

    draw_digital_num(sprite, &digital_num, x, y);
    digital_num.active = active_segments(minute_digits[0]);
    x += DIGIT_WIDTH + (DIGIT_PADDING * 2);

    // draw colon separating hour and minute digits
    sprite->fillRect(x, y + (digit_height / 2) - (digit_height / 4) - (DIGIT_THICKNESS / 2),
        DIGIT_THICKNESS, DIGIT_THICKNESS,
        CLOCK_COLON_COLOR);

    sprite->fillRect(x, y + (digit_height / 2) + (digit_height / 4) - (DIGIT_THICKNESS / 2),
        DIGIT_THICKNESS, DIGIT_THICKNESS,
        CLOCK_COLON_COLOR);

    x += DIGIT_THICKNESS + (DIGIT_PADDING * 2);

    // draw minute digits, update segments for next digits
    draw_digital_num(sprite, &digital_num, x, y);
    digital_num.active = active_segments(minute_digits[1]);
    x += DIGIT_WIDTH + (DIGIT_PADDING * 2);

    draw_digital_num(sprite, &digital_num, x, y);
    digital_num.active = active_segments(second_digits[0]);
    x += DIGIT_WIDTH + (DIGIT_PADDING * 2);

    // draw colon separating minute and second digits
    sprite->fillRect(x, y + (digit_height / 2) - (digit_height / 4) - (DIGIT_THICKNESS / 2),
        DIGIT_THICKNESS, DIGIT_THICKNESS,
        CLOCK_COLON_COLOR);

    sprite->fillRect(x, y + (digit_height / 2) + (digit_height / 4) - (DIGIT_THICKNESS / 2),
        DIGIT_THICKNESS, DIGIT_THICKNESS,
        CLOCK_COLON_COLOR);

    x += DIGIT_THICKNESS + (DIGIT_PADDING * 2);

    // draw second digits
    draw_digital_num(sprite, &digital_num, x, y);
    digital_num.active = active_segments(second_digits[1]);
    x += DIGIT_WIDTH + (DIGIT_PADDING * 2);

    draw_digital_num(sprite, &digital_num, x, y);
}
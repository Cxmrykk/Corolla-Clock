#include "digital_num.h"

// clock colon colour RGB565
#define CLOCK_COLON_COLOR ((12 << 11) | (40 << 5) | 12)

// digit colours RGB565
#define DIGIT_COLOR_ACTIVE ((12 << 11) | (40 << 5) | 12)
#define DIGIT_COLOR_INACTIVE ((4 << 11)  | (12 << 5) | 4)

// digit dimensions (must be even number)
#define DIGIT_PADDING 4
#define DIGIT_WIDTH 64
#define DIGIT_THICKNESS 12

uint16_t clock_height();
uint16_t clock_width();
void draw_digital_clock(TFT_eSprite *sprite, uint16_t x, uint16_t y, uint8_t hour, uint8_t minute, uint8_t second);
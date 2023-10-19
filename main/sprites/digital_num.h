#include <stdint.h>
#include <TFT_eSPI.h>

typedef struct {
    uint16_t thickness;
    uint16_t padding;
    uint16_t width;
    uint16_t color_active;
    uint16_t color_inactive;
    bool* active; // top to bottom, left to right
} digital_num_t;

// 0 - 9, element 11 is for undefined
static bool segments_num_table[11][7] = {
    { 1, 1, 1, 0, 1, 1, 1 },
    { 0, 0, 1, 0, 0, 1, 0 },
    { 1, 0, 1, 1, 1, 0, 1 },
    { 1, 0, 1, 1, 0, 1, 1 },
    { 0, 1, 1, 1, 0, 1, 0 },
    { 1, 1, 0, 1, 0, 1, 1 },
    { 1, 1, 0, 1, 1, 1, 1 },
    { 1, 0, 1, 0, 0, 1, 0 },
    { 1, 1, 1, 1, 1, 1 ,1 },
    { 1 ,1 ,1 ,1 ,0 ,1 ,1 },
    { 0, 0, 0, 0, 0, 0, 0 }
};

void draw_digital_num(TFT_eSprite *sprite, digital_num_t *digital_num, uint16_t x, uint16_t y);
bool* active_segments(uint8_t value);
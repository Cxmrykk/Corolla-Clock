#ifndef RGB565_H
#define RGB565_H

    #include <stdint.h>

    #define RED_MAXIMUM   0b011111 // 5 bits (0-31)
    #define GREEN_MAXIMUM 0b111111 // 6 bits (0-63)
    #define BLUE_MAXIMUM  0b011111 // 5 bits (0-31)

    typedef struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } Color_t;

    void increment_color(Color_t *color, bool opposite);
    void update_colors(Color_t *hue, Color_t *foreground, Color_t *background, uint8_t foreground_level, uint8_t background_level);
    void apply_white(Color_t *color, uint8_t level);
    void apply_black(Color_t *color, uint8_t level);
    uint16_t to_rgb565(Color_t *color);

#endif
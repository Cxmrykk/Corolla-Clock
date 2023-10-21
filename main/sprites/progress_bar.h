#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

    #include <stdint.h>
    #include <TFT_eSPI.h>

    #define BAR_WIDTH 400
    #define BAR_HEIGHT 40
    #define BAR_BORDER 8
    #define BAR_PADDING 4

    void draw_progress_bar(TFT_eSprite *sprite, uint16_t x, uint16_t y, float progress);

#endif
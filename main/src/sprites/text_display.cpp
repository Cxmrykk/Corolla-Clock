#include "sprites/text_display.h"
#include <TFT_eSPI.h>

void draw_text_display(TFT_eSprite *sprite, int lines, int x, int y, const char **contents) {
    for (int i = 0; i < lines; i++) {
        sprite->drawString((char*) contents[i], x, y + i * TEXT_HEIGHT_OFFSET, 4);
    }
}
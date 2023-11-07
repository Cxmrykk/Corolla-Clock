#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

    #include <TFT_eSPI.h>
    
    #define TEXT_HEIGHT_OFFSET 26

    void draw_text_display(TFT_eSprite *sprite, int lines, int x, int y, const char **contents);

#endif
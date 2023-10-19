#include "digital_num.h"

void draw_digital_num(TFT_eSprite *sprite, digital_num_t *digital_num, uint16_t x, uint16_t y) {
    uint16_t rect_thickness = digital_num->width - (digital_num->thickness * 2) - (digital_num->padding * 2);
    
    /*
        Layer 1 (CENTER) ◥■◤
    */
    sprite->fillTriangle(x + digital_num->padding, y,
        x + digital_num->padding + digital_num->thickness, y,
        x + digital_num->padding + digital_num->thickness, y + digital_num->thickness,
        digital_num->active[0] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillRect(x + digital_num->padding + digital_num->thickness, y,
        rect_thickness, digital_num->thickness + 1,
        digital_num->active[0] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillTriangle(x + digital_num->padding + digital_num->thickness + rect_thickness, y + digital_num->thickness,
        x + digital_num->padding + digital_num->thickness + rect_thickness, y,
        x + digital_num->padding + (digital_num->thickness * 2) + rect_thickness, y,
        digital_num->active[0] ? digital_num->color_active : digital_num->color_inactive);

    /*
        Layer 2 (LEFT) 
        ◣
        ■
        ▼
    */
    sprite->fillTriangle(x, y + digital_num->padding,
        x, y + digital_num->padding + digital_num->thickness,
        x + digital_num->thickness, y + digital_num->padding + digital_num->thickness,
        digital_num->active[1] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillRect(x, y + digital_num->padding + digital_num->thickness,
        digital_num->thickness + 1, rect_thickness,
        digital_num->active[1] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillTriangle(x, y + digital_num->padding + digital_num->thickness + rect_thickness,
        x + (digital_num->thickness * 0.5), y + digital_num->padding + (digital_num->thickness * 1.5) + rect_thickness,
        x + digital_num->thickness, y + digital_num->padding + digital_num->thickness + rect_thickness,
        digital_num->active[1] ? digital_num->color_active : digital_num->color_inactive);

    /*
        Layer 2 (RIGHT)
        ◢
        ■
        ▼
    */
    sprite->fillTriangle(x + (digital_num->padding * 2) + (digital_num->thickness * 2) + rect_thickness, y + digital_num->padding,
        x + (digital_num->padding * 2) + (digital_num->thickness * 2) + rect_thickness, y + digital_num->padding + digital_num->thickness,
        x + (digital_num->padding * 2) + digital_num->thickness + rect_thickness, y + digital_num->padding + digital_num->thickness,
        digital_num->active[2] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillRect(x + (digital_num->padding * 2) + digital_num->thickness + rect_thickness, y + digital_num->padding + digital_num->thickness,
        digital_num->thickness + 1, rect_thickness,
        digital_num->active[2] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillTriangle(x + (digital_num->padding * 2) + digital_num->thickness + rect_thickness, y + digital_num->padding + digital_num->thickness + rect_thickness,
        x + (digital_num->padding * 2) + (digital_num->thickness * 1.5) + rect_thickness, y + digital_num->padding + (digital_num->thickness * 1.5) + rect_thickness,
        x + (digital_num->padding * 2) + (digital_num->thickness * 2) + rect_thickness, y + digital_num->padding + digital_num->thickness + rect_thickness,
        digital_num->active[2] ? digital_num->color_active : digital_num->color_inactive);

    /*
        Layer 3 (CENTER) ◀■▶
    */
    sprite->fillTriangle(x + digital_num->padding + (digital_num->thickness * 0.5), y + (digital_num->padding * 2) + (digital_num->thickness * 1.5) + rect_thickness,
        x + digital_num->padding + digital_num->thickness, y + (digital_num->padding * 2) + digital_num->thickness + rect_thickness,
        x + digital_num->padding + digital_num->thickness, y + (digital_num->padding * 2) + (digital_num->thickness * 2) + rect_thickness,
        digital_num->active[3] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillRect(x + digital_num->padding + digital_num->thickness, y + (digital_num->padding * 2) + digital_num->thickness + rect_thickness,
        rect_thickness, digital_num->thickness + 1,
        digital_num->active[3] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillTriangle(x + digital_num->padding + digital_num->thickness + rect_thickness, y + (digital_num->padding * 2) + digital_num->thickness + rect_thickness,
        x + digital_num->padding + (digital_num->thickness * 1.5) + rect_thickness, y + (digital_num->padding * 2) + (digital_num->thickness * 1.5) + rect_thickness,
        x + digital_num->padding + digital_num->thickness + rect_thickness, y + (digital_num->padding * 2) + (digital_num->thickness * 2) + rect_thickness,
        digital_num->active[3] ? digital_num->color_active : digital_num->color_inactive);

    /*
        Layer 4 (LEFT)
        ▲
        ■
        ◤
    */
    sprite->fillTriangle(x, y + (digital_num->padding * 3) + (digital_num->thickness * 2) + rect_thickness,
        x + (digital_num->thickness * 0.5), y + (digital_num->padding * 3) + (digital_num->thickness * 1.5) + rect_thickness,
        x + digital_num->thickness, y + (digital_num->padding * 3) + (digital_num->thickness * 2) + rect_thickness,
        digital_num->active[4] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillRect(x, y + (digital_num->padding * 3) + (digital_num->thickness * 2) + rect_thickness,
        digital_num->thickness + 1, rect_thickness,
        digital_num->active[4] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillTriangle(x + digital_num->thickness, y + (digital_num->padding * 3) + (digital_num->thickness * 2) + (rect_thickness * 2),
        x, y + (digital_num->padding * 3) + (digital_num->thickness * 2) + (rect_thickness * 2),
        x, y + (digital_num->padding * 3) + (digital_num->thickness * 3) + (rect_thickness * 2),
        digital_num->active[4] ? digital_num->color_active : digital_num->color_inactive);

    /*
        Layer 4 (RIGHT)
        ▲
        ■
        ◥
    */
    sprite->fillTriangle(x + (digital_num->padding * 2) + digital_num->thickness + rect_thickness, y + (digital_num->padding * 3) + (digital_num->thickness * 2) + rect_thickness,
        x + (digital_num->padding * 2) + (digital_num->thickness * 1.5) + rect_thickness, y + (digital_num->padding * 3) + (digital_num->thickness * 1.5) + rect_thickness,
        x + (digital_num->padding * 2) + (digital_num->thickness * 2) + rect_thickness, y + (digital_num->padding * 3) + (digital_num->thickness * 2) + rect_thickness,
        digital_num->active[5] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillRect(x + (digital_num->padding * 2) + digital_num->thickness + rect_thickness,  y + (digital_num->padding * 3) + (digital_num->thickness * 2) + rect_thickness,
        digital_num->thickness + 1, rect_thickness,
        digital_num->active[5] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillTriangle(x + (digital_num->padding * 2) + digital_num->thickness + rect_thickness, y + (digital_num->padding * 3) + (digital_num->thickness * 2) + (rect_thickness * 2),
        x + (digital_num->padding * 2) + (digital_num->thickness * 2) + rect_thickness, y + (digital_num->padding * 3) + (digital_num->thickness * 2) + (rect_thickness * 2),
        x + (digital_num->padding * 2) + (digital_num->thickness * 2) + rect_thickness, y + (digital_num->padding * 3) + (digital_num->thickness * 3) + (rect_thickness * 2),
        digital_num->active[5] ? digital_num->color_active : digital_num->color_inactive);

    /*
        Layer 5 (CENTER) ◢■◣
    */
    sprite->fillTriangle(x + digital_num->padding, y + (digital_num->padding * 4) + (digital_num->thickness * 3) + (rect_thickness * 2),
        x + digital_num->padding + digital_num->thickness, y + (digital_num->padding * 4) + (digital_num->thickness * 3) + (rect_thickness * 2),
        x + digital_num->padding + digital_num->thickness, y + (digital_num->padding * 4) + (digital_num->thickness * 2) + (rect_thickness * 2),
        digital_num->active[6] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillRect(x + digital_num->padding + digital_num->thickness, y + (digital_num->padding * 4) + (digital_num->thickness * 2) + (rect_thickness * 2),
        rect_thickness, digital_num->thickness + 1,
        digital_num->active[6] ? digital_num->color_active : digital_num->color_inactive);

    sprite->fillTriangle(x + digital_num->padding + digital_num->thickness + rect_thickness, y + (digital_num->padding * 4) + (digital_num->thickness * 2) + (rect_thickness * 2),
        x + digital_num->padding + digital_num->thickness + rect_thickness, y + (digital_num->padding * 4) + (digital_num->thickness * 3) + (rect_thickness * 2),
        x + digital_num->padding + (digital_num->thickness * 2) + rect_thickness, y + (digital_num->padding * 4) + (digital_num->thickness * 3) + (rect_thickness * 2),
        digital_num->active[6] ? digital_num->color_active : digital_num->color_inactive);
}

bool* active_segments(uint8_t value) {
    if (0 <= value && value <= 9) {
        return segments_num_table[value];
    } else {
        return segments_num_table[11]; // undefined number
    }
}
#include "sprites/tools/rgb565.h"

/*
    Red:
    - increases when blue is maximum (green is 0)
    - decreases when green is maximum (blue is 0)

    Green:
    - increases when red is maximum (blue is 0)
    - decreases when blue is maximum (red is 0)

    Blue:
    - increases when green is maximum (red is 0)
    - decreases when red is maximum (green is 0)

    Increase/decrease swap when going opposite direction
*/
void increment_color(Color_t *color, bool opposite) {
    // colours have reached maximum value
    bool red_max = color->r == RED_MAXIMUM;
    bool green_max = color->g == GREEN_MAXIMUM;
    bool blue_max = color->b == BLUE_MAXIMUM;

    // colours have reached minimum value
    bool red_min = color->r == 0;
    bool green_min = color->g == 0;
    bool blue_min = color->b == 0;

    if (opposite) {
        // apply red increase/decrease
        if (color->r < RED_MAXIMUM && green_max && blue_min) {
            color->r++;
        }

        if (color->r > 0 && blue_max && green_min) {
            color->r--;
        }

        // apply green increase/decrease
        if (color->g < GREEN_MAXIMUM && blue_max && red_min) {
            color->g++;
        }

        if (color->g > 0 && red_max && blue_min) {
            color->g--;
        }

        // apply blue increase/decrease
        if (color->b > 0 && green_max && red_min) {
            color->b--;
        }

        if (color->b < BLUE_MAXIMUM && red_max && green_min) {
            color->b++;
        }
    } else {
        // apply red increase/decrease
        if (color->r < RED_MAXIMUM && blue_max && green_min) {
            color->r++;
        }

        if (color->r > 0 && green_max && blue_min) {
            color->r--;
        }

        // apply green increase/decrease
        if (color->g < GREEN_MAXIMUM && red_max && blue_min) {
            color->g++;
        }

        if (color->g > 0 && blue_max && red_min) {
            color->g--;
        }

        // apply blue increase/decrease
        if (color->b < BLUE_MAXIMUM && green_max && red_min) {
            color->b++;
        }

        if (color->b > 0 && red_max && green_min) {
            color->b--;
        }
    }
}

void update_colors(Color_t *hue, Color_t *foreground, Color_t *background, uint8_t foreground_level, uint8_t background_level) {
    // reset foreground and apply new level
    foreground->r = hue->r;
    foreground->g = hue->g;
    foreground->b = hue->b;
    apply_white(foreground, foreground_level);
    // reset background and apply new level
    background->r = foreground->r;
    background->g = foreground->g;
    background->b = foreground->b;
    apply_black(background, background_level);
}


// level is 63 maximum (5 bits)
void apply_white(Color_t *color, uint8_t level) {
    float multiplier = (float) level / (float) GREEN_MAXIMUM;
    color->r += (uint8_t) ((float) (RED_MAXIMUM - color->r) * multiplier);
    color->g += (uint8_t) ((float) (GREEN_MAXIMUM - color->g) * multiplier);
    color->b += (uint8_t) ((float) (BLUE_MAXIMUM - color->b) * multiplier);
}

// level is 63 maximum (5 bits)
void apply_black(Color_t *color, uint8_t level) {
    float multiplier = (float) level / (float) GREEN_MAXIMUM;
    color->r = (uint8_t) (color->r * multiplier);
    color->g = (uint8_t) (color->g * multiplier);
    color->b = (uint8_t) (color->b * multiplier);
}

uint16_t to_rgb565(Color_t *color) {
    return ((color->r << 11) | (color->g << 5) | (color->b));
}
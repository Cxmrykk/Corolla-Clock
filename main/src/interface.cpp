#include "interface.h"
#include "drivers/rm67162.h"
#include "drivers/gpio_states.h"

/*
    Mode 0: Set Clock Time (Default)
    - H: Increase hour
    - M: Increase minute
*/
void set_clock_time_default(Clock_State_t *state) {
    if (gpio.hour.pressed) {
        state->timer.hour++;
        if (state->timer.hour >= 24) {
            state->timer.hour = 0;
        }
        state->timer.second = 0;
    }
    if (gpio.minute.pressed) {
        state->timer.minute++;
        if (state->timer.minute >= 60) {
            state->timer.minute = 0;
        }
        state->timer.second = 0;
    }
}

/*
    Mode 1: Set Horizontal Alignment
    - H: Move Screen Left
    - M: Move Screen Right
*/
void set_horizontal_alignment(Clock_State_t *state) {
    if (gpio.hour.held) {
        state->offset[0]--;
    }
    if (gpio.minute.held) {
        state->offset[0]++;
    }
}

/*
    Mode 2: Set Vertical Alignment
    - H: Move Screen Up
    - M: Move Screen Down
*/
void set_vertical_alignment(Clock_State_t *state) {
    if (gpio.hour.held) {
        state->offset[1]--;
    }
    if (gpio.minute.held) {
        state->offset[1]++;
    }
}

/*
    Mode 3: Set Brightness
    - H: Increase Brightness
    - M: Decrease Brightness
*/
void set_brightness(Clock_State_t *state) {
    if (gpio.hour.held && state->profile->brightness < MAX_BRIGHTNESS) {
        state->profile->brightness++;
        lcd_brightness(state->profile->brightness);
    }
    if (gpio.minute.held && state->profile->brightness > MIN_BRIGHTNESS) {
        state->profile->brightness--;
        lcd_brightness(state->profile->brightness);
    }
}

/*
    Mode 4: Set Colour
    - H: Set Colour Hue
    - M: Set White Level
*/
void set_color(Clock_State_t *state) {
    if (gpio.hour.held) {
        increment_color(state->profile->hue, false);
        update_colors(state->profile->hue,
            state->profile->digital_clock->color_active,
            state->profile->digital_clock->color_inactive,
            state->profile->whiteness,
            state->profile->opacity);
    }

    if (gpio.minute.held) {
        if (gpio.minute.pressed) {
            state->whiteness_toggle = !state->whiteness_toggle;
        }
        if (state->whiteness_toggle && state->profile->whiteness < GREEN_MAXIMUM) {
            state->profile->whiteness++;
            update_colors(state->profile->hue,
                state->profile->digital_clock->color_active,
                state->profile->digital_clock->color_inactive,
                state->profile->whiteness,
                state->profile->opacity);
        } else if (!state->whiteness_toggle && state->profile->whiteness > 0) {
            state->profile->whiteness--;
            update_colors(state->profile->hue,
                state->profile->digital_clock->color_active,
                state->profile->digital_clock->color_inactive,
                state->profile->whiteness,
                state->profile->opacity);
        }
    }
}

/*
    Mode 5: Set Background Opacity
    - H: Increase Opacity
    - M: Decrease Opacity
*/
void set_background_opacity(Clock_State_t *state) {
    if (gpio.hour.held && state->profile->opacity < GREEN_MAXIMUM) {
        state->profile->opacity++;
        update_colors(state->profile->hue,
            state->profile->digital_clock->color_active,
            state->profile->digital_clock->color_inactive,
            state->profile->whiteness,
            state->profile->opacity);
    }
    if (gpio.minute.held && state->profile->opacity > 0) {
        state->profile->opacity--;
        update_colors(state->profile->hue,
            state->profile->digital_clock->color_active,
            state->profile->digital_clock->color_inactive,
            state->profile->whiteness,
            state->profile->opacity);
    }
}

/*
    Mode 6: Set Clock Size
    - H: Increase Size
    - M: Decrease Size
*/
void set_clock_size(Clock_State_t *state) {
    if (gpio.hour.pressed) {
        state->lamp_on_profile.digital_clock->width += 2;
        state->lamp_off_profile.digital_clock->width += 2;
        update_clock_offset(state);
    }
    if (gpio.minute.pressed && state->profile->digital_clock->width > 2) {
        state->lamp_on_profile.digital_clock->width -= 2;
        state->lamp_off_profile.digital_clock->width -= 2;
        update_clock_offset(state);
    }
}

/*
    Mode 7: Set Clock Thickness
    - H: Increase Thickness
    - M: Decrease Thickness
*/
void set_clock_thickness(Clock_State_t *state) {
    if (gpio.hour.pressed) {
        state->lamp_on_profile.digital_clock->thickness += 2;
        state->lamp_off_profile.digital_clock->thickness += 2;
        update_clock_offset(state);
    }
    if (gpio.minute.pressed && state->profile->digital_clock->thickness > 2) {
        state->lamp_on_profile.digital_clock->thickness -= 2;
        state->lamp_off_profile.digital_clock->thickness -= 2;
        update_clock_offset(state);
    }
}

/*
    Mode 8: Set Clock Padding
    - H: Increase Padding
    - M: Decrease Padding
*/
void set_clock_padding(Clock_State_t *state) {
    if (gpio.hour.pressed) {
        state->lamp_on_profile.digital_clock->padding += 1;
        state->lamp_off_profile.digital_clock->padding += 1;
        update_clock_offset(state);
    }
    if (gpio.minute.pressed && state->profile->digital_clock->padding > 1) {
        state->lamp_on_profile.digital_clock->padding -= 1;
        state->lamp_off_profile.digital_clock->padding -= 1;
        update_clock_offset(state);
    }
}
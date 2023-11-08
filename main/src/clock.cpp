#include <Arduino.h>
#include <TFT_eSPI.h>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>

#include "clock.h"
#include "interface.h"
#include "drivers/rm67162.h"
#include "drivers/gpio_states.h"
#include "sprites/digital_clock.h"
#include "sprites/text_display.h"
#include "sprites/tools/rgb565.h"

void update_clock_offset(Clock_State_t *state) {
    state->clock_offset[0] = (CANVAS_X - clock_width(state->profile->digital_clock)) / 2;
    state->clock_offset[1] = (CANVAS_Y - clock_height(state->profile->digital_clock)) / 2;
}

void timeout_handler(Clock_State_t *state) {
    if (state->time_updated && !state->screen_toggle) {
        state->time_updated = 0;

        // reduce timeout by 1 second
        if (state->timeout > 0) {
            state->timeout--;
        }

        // turn off display brightness (smooth transition)
        if (state->timeout == TIMEOUT_BRIGHTNESS) {
            lcd_brightness(MIN_BRIGHTNESS);
        }
        // turn off display
        if (state->timeout == TIMEOUT_DISPLAY) {
            lcd_display_off();
        }
    }
}

void draw_handler(Clock_State_t *state) {
    /*
        Don't draw components when screen is off
    */
    if (state->timeout <= TIMEOUT_DISPLAY) {
        return;
    }

    state->sprite.fillSprite(TFT_BLACK);

    /*
        Display a border around the canvas if alignment is toggled
    */
    if (state->mode == 1 || state->mode == 2) {
        state->sprite.drawRect(state->offset[0] - 1, state->offset[1] - 1, CANVAS_X + 2, CANVAS_Y + 2, TFT_WHITE);
    }

    /*
        Draw the clock
    */
    draw_digital_clock(&state->sprite, state->profile->digital_clock, state->clock_offset[0] + state->offset[0], state->clock_offset[1] + state->offset[1]);

    /*
        Display the mode as text at the bottom of the screen
    */
    if (state->mode_toggle) {
        if (state->mode < 9) {
            int x = state->offset[0] < 0 ? 0 : state->offset[0];
            int y = state->offset[1] < 0 ? 0 : state->offset[1];
            draw_text_display(&state->sprite, 3, x, y, clock_functions_text[state->mode]);
        }
    }

    lcd_PushColors(0, 0, SCREEN_X, SCREEN_Y, (uint16_t*) state->sprite.getPointer());
}

void gpio_handler(Clock_State_t *state) {
    get_GPIO_states();

    /*
        Set clock profile from GPIO_LAMP state
    */
    if (gpio.lamp.held) {
        if (!state->lamp_toggle) {
            state->profile = &state->lamp_on_profile;
            update_clock_offset(state);
            lcd_brightness(state->profile->brightness);
        }
        state->lamp_toggle = 1;

    } else {
        if (state->lamp_toggle) {
            state->profile = &state->lamp_off_profile;
            update_clock_offset(state);
            lcd_brightness(state->profile->brightness);
        }
        state->lamp_toggle = 0;
    }

    /*
        Set AMOLED screen state from accessory
    */
    if (gpio.accessory.held) {
        if (!state->screen_toggle) {
            lcd_brightness(state->profile->brightness);
            lcd_display_on();
        }

        state->screen_toggle = 1;
        state->timeout = TIMEOUT_DURATION;
    } else {
        state->screen_toggle = 0;
        if (gpio.reset.pressed || gpio.hour.pressed || gpio.minute.pressed) {
            if (state->timeout <= TIMEOUT_DISPLAY) {
                lcd_brightness(state->profile->brightness);
                lcd_display_on();
            } else

            if (state->timeout <= TIMEOUT_BRIGHTNESS) {
                lcd_brightness(state->profile->brightness);
            }

            // cancel normal button operation
            if (state->timeout <= TIMEOUT_BRIGHTNESS) {
                state->timeout = TIMEOUT_DURATION;
                return;
            }

            state->timeout = TIMEOUT_DURATION;
        }
    }

    /*
        Mode selection menu toggled
    */
    if (state->mode_toggle) {
        if (gpio.hour.pressed && state->mode < 8) {
            state->mode++;
        }

        if (gpio.minute.pressed && state->mode > 0) {
            state->mode--;
        }

    /*
        Handle button operations per current mode
    */
    } else {
        clock_functions[state->mode](state);
    }

    /*
        Toggle mode selection menu
    */
    if (gpio.reset.pressed) {
        state->mode_toggle = !state->mode_toggle;
    }
}
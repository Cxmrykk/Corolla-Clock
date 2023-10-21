#include <Arduino.h>
#include <TFT_eSPI.h>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>

#include "digital_clock.h"
#include "driver/rm67162.h"
#include "main.h"
#include "rgb565.h"
#include "gpio_states.h"

// lamp off clock colours
color_t lamp_off_hue = { 0, GREEN_MAXIMUM, 0 };
color_t lamp_off_foreground = {0, GREEN_MAXIMUM, 0 };
color_t lamp_off_background = { 0, GREEN_MAXIMUM / 10, 0 };

// lamp on clock colours
color_t lamp_on_hue = { RED_MAXIMUM, 0, 0 };
color_t lamp_on_foreground = {RED_MAXIMUM, 0, 0 };
color_t lamp_on_background = { RED_MAXIMUM / 10, 0, 0 };

// initialise clock
clock_state_t clock_state = {
    .hour = 0,
    .minute = 0,
    .second = 0
};

digital_clock_t lamp_on_digital_clock = {
    &clock_state,
    &lamp_on_foreground,
    &lamp_on_background,
    DIGIT_PADDING,
    DIGIT_WIDTH,
    DIGIT_THICKNESS
};

digital_clock_t lamp_off_digital_clock = {
    &clock_state,
    &lamp_off_foreground,
    &lamp_off_background,
    DIGIT_PADDING,
    DIGIT_WIDTH,
    DIGIT_THICKNESS
};

clock_profile_t lamp_on_profile = {
    &lamp_on_digital_clock,
    &lamp_on_hue,
    LAMP_ON_BRIGHTNESS,
    0,
    0
};

clock_profile_t lamp_off_profile = {
    &lamp_off_digital_clock,
    &lamp_off_hue,
    LAMP_OFF_BRIGHTNESS,
    0,
    0
};

clock_profile_t* profile = &lamp_off_profile;

// canvas offset
uint16_t offset[2] = { 0, 0 };

// clock offset (centered)
uint16_t clock_offset[2] = {
    (uint16_t) ((CANVAS_X - clock_width(profile->digital_clock)) / 2),
    (uint16_t) ((CANVAS_Y - clock_height(profile->digital_clock)) / 2)
};

// timeout event (resets when accessory is on)
uint8_t timeout = TIMEOUT_DURATION;

// button toggles
bool mode_toggle = 0;
bool lamp_toggle = 0;
bool screen_toggle = 0;
bool whiteness_toggle = 0;

bool time_updated = 0;

// current mode
uint8_t mode = 0;

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

void update_clock_offset() {
    clock_offset[0] = (CANVAS_X - clock_width(profile->digital_clock)) / 2;
    clock_offset[1] = (CANVAS_Y - clock_height(profile->digital_clock)) / 2;
}

void increment_timer() {
    clock_state.second++;
    time_updated = 1;
    
    // 60 seconds have passed
    if (clock_state.second >= 60) {
        clock_state.second = 0;
        clock_state.minute++;

        // 60 minutes have passed
        if (clock_state.minute >= 60) {
            clock_state.minute = 0;
            clock_state.hour++;

            // 24 hours have passed
            if (clock_state.hour >= 24) {
                clock_state.hour = 0;
            }
        }
    }
}

void setup() { 
    rm67162_init(); // amoled initialization
    lcd_setRotation(3);
    sprite.createSprite(SCREEN_X, SCREEN_Y);
    sprite.setSwapBytes(1);

    // set GPIO direction
    gpio_set_direction(GPIO_ACC, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_LAMP, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_RESET, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_HOUR, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_MINUTE, GPIO_MODE_INPUT);

    // car signals VCC
    gpio_set_pull_mode(GPIO_ACC, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GPIO_LAMP, GPIO_PULLDOWN_ONLY);

    // buttons 3.3V
    gpio_set_pull_mode(GPIO_RESET, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GPIO_HOUR, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GPIO_MINUTE, GPIO_PULLDOWN_ONLY);

    // initialise timer
    esp_timer_handle_t periodic_timer;
    const esp_timer_create_args_t periodic_timer_args = {
            .callback = (esp_timer_cb_t) &increment_timer,
            .name = "periodic"
    };
    esp_timer_create(&periodic_timer_args, &periodic_timer);
    esp_timer_start_periodic(periodic_timer, 1000000); // 1 second interval
}

void timeout_handler() {
    if (time_updated && !screen_toggle) {
        time_updated = 0;

        // reduce timeout by 1 second
        if (timeout > 0) {
            timeout--;
        }

        // turn off display brightness (smooth transition)
        if (timeout == TIMEOUT_BRIGHTNESS) {
            lcd_brightness(MIN_BRIGHTNESS);
        }
        // turn off display
        if (timeout == TIMEOUT_DISPLAY) {
            lcd_display_off();
        }
    }
}

void draw_handler() {
    /*
        Don't draw components when screen is off
    */
    if (timeout <= TIMEOUT_DISPLAY) {
        return;
    }

    sprite.fillSprite(TFT_BLACK);

    /*
        Display a border around the canvas if alignment is toggled
    */
    if (mode_toggle && (mode == 1 || mode == 2)) {
        sprite.drawRect(offset[0] - 1, offset[1] - 1, CANVAS_X + 2, CANVAS_Y + 2, TFT_WHITE);
    }

    /*
        Draw the clock
    */
    draw_digital_clock(&sprite, profile->digital_clock, clock_offset[0] + offset[0], clock_offset[1] + offset[1]);

    /*
        Display the mode as text at the bottom of the screen
    */
    if (mode_toggle) {
        switch (mode) {
            case 0:
                sprite.drawString("Set Time", offset[0], offset[1], 4);
                sprite.drawString("H: Set hour", offset[0], offset[1] + 26, 4);
                sprite.drawString("M: Set minute", offset[0], offset[1] + 52, 4);
                break;
            case 1:
                sprite.drawString("Set Horizontal Alignment", offset[0], offset[1], 4);
                sprite.drawString("H: Move display left", offset[0], offset[1] + 26, 4);
                sprite.drawString("M: Move display right", offset[0], offset[1] + 52, 4);
                break;
            case 2:
                sprite.drawString("Set Vertical Alignment", offset[0], offset[1], 4);
                sprite.drawString("H: Move display up", offset[0], offset[1] + 26, 4);
                sprite.drawString("M: Move display down", offset[0], offset[1] + 52, 4);
                break;
            case 3:
                sprite.drawString("Set Brightness", offset[0], offset[1], 4);
                sprite.drawString("H: Increase brightness", offset[0], offset[1] + 26, 4);
                sprite.drawString("M: Decrease brightness", offset[0], offset[1] + 52, 4);
                break;
            case 4:
                sprite.drawString("Set Colour", offset[0], offset[1], 4);
                sprite.drawString("H: Set Hue", offset[0], offset[1] + 26, 4);
                sprite.drawString("M: Set Brightness", offset[0], offset[1] + 52, 4);
                break;
            case 5:
                sprite.drawString("Set Opacity", offset[0], offset[1], 4);
                sprite.drawString("H: Increase Opacity", offset[0], offset[1] + 26, 4);
                sprite.drawString("M: Decrease Opacity", offset[0], offset[1] + 52, 4);
                break;
            case 6:
                sprite.drawString("Set Clock Size", offset[0], offset[1], 4);
                sprite.drawString("H: Increase Size", offset[0], offset[1] + 26, 4);
                sprite.drawString("M: Decrease Size", offset[0], offset[1] + 52, 4);
                break;
            case 7:
                sprite.drawString("Set Clock Thickness", offset[0], offset[1], 4);
                sprite.drawString("H: Increase Thickness", offset[0], offset[1] + 26, 4);
                sprite.drawString("M: Decrease Thickness", offset[0], offset[1] + 52, 4);
                break;
            case 8:
                sprite.drawString("Set Clock Padding", offset[0], offset[1], 4);
                sprite.drawString("H: Increase Padding", offset[0], offset[1] + 26, 4);
                sprite.drawString("M: Decrease Padding", offset[0], offset[1] + 52, 4);
                break;
        }
    }

    lcd_PushColors(0, 0, SCREEN_X, SCREEN_Y, (uint16_t*) sprite.getPointer());
}

void gpio_handler() {
    get_GPIO_states();

    /*
        Set clock profile from GPIO_LAMP state
    */
    if (gpio.lamp.held) {
        if (!lamp_toggle) {
            profile = &lamp_on_profile;
            update_clock_offset();
            lcd_brightness(profile->brightness);
        }
        lamp_toggle = 1;

    } else {
        if (lamp_toggle) {
            profile = &lamp_off_profile;
            update_clock_offset();
            lcd_brightness(profile->brightness);
        }
        lamp_toggle = 0;
    }

    /*
        Set AMOLED screen state from accessory
    */
    if (gpio.accessory.held) {
        if (!screen_toggle) {
            lcd_brightness(profile->brightness);
            lcd_display_on();
        }

        screen_toggle = 1;
        timeout = TIMEOUT_DURATION;
    } else {
        screen_toggle = 0;
        if (gpio.reset.pressed || gpio.hour.pressed || gpio.minute.pressed) {
            if (timeout <= TIMEOUT_DISPLAY) {
                lcd_brightness(profile->brightness);
                lcd_display_on();
            } else

            if (timeout <= TIMEOUT_BRIGHTNESS) {
                lcd_brightness(profile->brightness);
            }

            timeout = TIMEOUT_DURATION;
        }

        // cancel normal button operation
        if (timeout <= TIMEOUT_BRIGHTNESS) {
            return;
        }
    }

    /*
        Mode selection menu toggled
    */
    if (mode_toggle) {
        if (gpio.hour.pressed && mode < 8) {
            mode++;
        }

        if (gpio.minute.pressed && mode > 0) {
            mode--;
        }

    /*
        Handle button operations per current mode
    */
    } else {
        switch (mode) {
            /*
                Mode 0: Set Clock Time (Default)
                - H: Increase hour
                - M: Increase minute
            */
            case 0:
                // increment hour
                if (gpio.hour.pressed) {
                    clock_state.hour++;
                    if (clock_state.hour >= 24) {
                        clock_state.hour = 0;
                    }
                    clock_state.second = 0;
                }
                // increment minute
                if (gpio.minute.pressed) {
                    clock_state.minute++;
                    if (clock_state.minute >= 60) {
                        clock_state.minute = 0;
                    }
                    clock_state.second = 0;
                }
                break;

            /*
                Mode 1: Set Horizontal Alignment
                - H: Move Screen Left
                - M: Move Screen Right
            */
            case 1:
                // horizontal left
                if (gpio.hour.held && offset[0] > 0) {
                    offset[0]--;
                }
                // horizontal right
                if (gpio.minute.held && offset[0] < (SCREEN_X - CANVAS_X)) {
                    offset[0]++;
                }
                break;

            /*
                Mode 2: Set Vertical Alignment
                - H: Move Screen Up
                - M: Move Screen Down
            */
            case 2:
                // vertical up
                if (gpio.hour.held && offset[1] > 0) {
                    offset[1]--;
                }
                // vertical down
                if (gpio.minute.held && offset[1] < (SCREEN_Y - CANVAS_Y)) {
                    offset[1]++;
                }
                break;

            /*
                Mode 3: Set Brightness
                - H: Increase Brightness
                - M: Decrease Brightness
            */
            case 3:
                if (gpio.hour.held && profile->brightness < MAX_BRIGHTNESS) {
                    profile->brightness++;
                    lcd_brightness(profile->brightness);
                }
                if (gpio.minute.held && profile->brightness > MIN_BRIGHTNESS) {
                    profile->brightness--;
                    lcd_brightness(profile->brightness);
                }
                break;

            /*
                Mode 4: Set Colour
                - H: Set Colour Hue
                - M: Set White Level
            */
            case 4:
                if (gpio.hour.held) {
                    increment_color(profile->hue, false);
                    update_colors(profile->hue,
                        profile->digital_clock->color_active,
                        profile->digital_clock->color_inactive,
                        profile->whiteness,
                        profile->opacity);
                }

                if (gpio.minute.held) {
                    // toggle direction on button press
                    if (gpio.minute.pressed) {
                        whiteness_toggle = !whiteness_toggle;
                    }

                    // increment whiteness value, update active colour
                    if (whiteness_toggle && profile->whiteness < GREEN_MAXIMUM) {
                        profile->whiteness++;
                        update_colors(profile->hue,
                            profile->digital_clock->color_active,
                            profile->digital_clock->color_inactive,
                            profile->whiteness,
                            profile->opacity);
                    } else

                    // decrement whiteness value, update active colour
                    if (!whiteness_toggle && profile->whiteness > 0) {
                        profile->whiteness--;
                        update_colors(profile->hue,
                            profile->digital_clock->color_active,
                            profile->digital_clock->color_inactive,
                            profile->whiteness,
                            profile->opacity);
                    }
                }
                break;

            /*
                Mode 5: Set Background Opacity
                - H: Increase Opacity
                - M: Decrease Opacity
            */
            case 5:
                if (gpio.hour.held && profile->opacity < GREEN_MAXIMUM) {
                    profile->opacity++;
                    update_colors(profile->hue, 
                        profile->digital_clock->color_active,
                        profile->digital_clock->color_inactive,
                        profile->whiteness,
                        profile->opacity);
                }

                if (gpio.minute.held && profile->opacity > 0) {
                    profile->opacity--;
                    update_colors(profile->hue, 
                        profile->digital_clock->color_active,
                        profile->digital_clock->color_inactive,
                        profile->whiteness,
                        profile->opacity);
                }
                break;

            /*
                Mode 6: Set Clock Size
                - H: Increase Size
                - M: Decrease Size
            */
            case 6:
                if (gpio.hour.pressed) {
                    profile->digital_clock->width += 2;
                    update_clock_offset();
                }
                if (gpio.minute.pressed && profile->digital_clock->width > 2) {
                    profile->digital_clock->width -= 2;
                    update_clock_offset();
                }
                break;

            /*
                Mode 7: Set Clock Thickness
                - H: Increase Thickness
                - M: Decrease Thickness
            */
            case 7:
                if (gpio.hour.pressed) {
                    profile->digital_clock->thickness += 2;
                    update_clock_offset();
                }
                if (gpio.minute.pressed && profile->digital_clock->thickness > 2) {
                    profile->digital_clock->thickness -= 2;
                    update_clock_offset();
                }
                break;

            /*
                Mode 8: Set Clock Padding
                - H: Increase Padding
                - M: Decrease Padding
            */
            case 8:
                if (gpio.hour.pressed) {
                    profile->digital_clock->padding += 2;
                    update_clock_offset();
                }
                if (gpio.minute.pressed && profile->digital_clock->padding > 2) {
                    profile->digital_clock->padding -= 2;
                    update_clock_offset();
                }
                break;
        }
    }

    /*
        Toggle mode selection menu
    */
    if (gpio.reset.pressed) {
        mode_toggle = !mode_toggle;
    }
}

void loop() {
    timeout_handler();
    gpio_handler();
    draw_handler();
    vTaskDelay(1000 / REFRESH_RATE);
}
#include <driver/gpio.h>

#include "drivers/gpio_states.h"

void get_GPIO_states() {
    // get actual GPIO high/low state
    GPIO_active.accessory = gpio_get_level(GPIO_ACC);
    GPIO_active.lamp = gpio_get_level(GPIO_LAMP);
    GPIO_active.reset = !gpio_get_level(GPIO_RESET);
    GPIO_active.hour = !gpio_get_level(GPIO_HOUR);
    GPIO_active.minute = !gpio_get_level(GPIO_MINUTE);

    // get interpreted GPIO high/low state (button held for cycle duration)
    gpio.accessory.held = GPIO_active.accessory && GPIO_cycle.accessory == GPIO_HOLD_COUNT;
    gpio.lamp.held = GPIO_active.lamp && GPIO_cycle.lamp == GPIO_HOLD_COUNT;
    gpio.reset.held = GPIO_active.reset && GPIO_cycle.reset == GPIO_HOLD_COUNT;
    gpio.hour.held = GPIO_active.hour && GPIO_cycle.hour == GPIO_HOLD_COUNT;
    gpio.minute.held = GPIO_active.minute && GPIO_cycle.minute == GPIO_HOLD_COUNT;

    // get toggled GPIO high/low state
    gpio.accessory.pressed = gpio.accessory.held && !GPIO_toggled.accessory;
    gpio.lamp.pressed = gpio.lamp.held && !GPIO_toggled.lamp;
    gpio.reset.pressed = gpio.reset.held && !GPIO_toggled.reset;
    gpio.hour.pressed = gpio.hour.held && !GPIO_toggled.hour;
    gpio.minute.pressed = gpio.minute.held && !GPIO_toggled.minute;

    /*
        Update GPIO cycle state (number of cycles required to interpret high state)
    */
    if (GPIO_active.accessory && GPIO_cycle.accessory < GPIO_HOLD_COUNT) {
        GPIO_cycle.accessory++;
    } else if (!GPIO_active.accessory && GPIO_cycle.accessory > 0) {
        GPIO_cycle.accessory--;
    }

    if (GPIO_active.lamp && GPIO_cycle.lamp < GPIO_HOLD_COUNT) {
        GPIO_cycle.lamp++;
    } else if (!GPIO_active.lamp && GPIO_cycle.lamp > 0) {
        GPIO_cycle.lamp--;
    }

    if (GPIO_active.reset && GPIO_cycle.reset < GPIO_HOLD_COUNT) {
        GPIO_cycle.reset++;
    } else if (!GPIO_active.reset && GPIO_cycle.reset > 0) {
        GPIO_cycle.reset--;
    }

    if (GPIO_active.hour && GPIO_cycle.hour < GPIO_HOLD_COUNT) {
        GPIO_cycle.hour++;
    } else if (!GPIO_active.hour && GPIO_cycle.hour > 0) {
        GPIO_cycle.hour--;
    }

    if (GPIO_active.minute && GPIO_cycle.minute < GPIO_HOLD_COUNT) {
        GPIO_cycle.minute++;
    } else if (!GPIO_active.minute && GPIO_cycle.minute > 0) {
        GPIO_cycle.minute--;
    }

    /*
        Toggle state on
    */
    if (gpio.accessory.pressed) {
        GPIO_toggled.accessory = 1;
    }

    if (gpio.lamp.pressed) {
        GPIO_toggled.lamp = 1;
    }
    
    if (gpio.reset.pressed) {
        GPIO_toggled.reset = 1;
    }

    if (gpio.hour.pressed) {
        GPIO_toggled.hour = 1;
    }

    if (gpio.minute.pressed) {
        GPIO_toggled.minute = 1;
    }

    /*
        Toggle state off
    */
    if (!gpio.accessory.held && GPIO_toggled.accessory) {
        GPIO_toggled.accessory = 0;
    }

    if (!gpio.lamp.held && GPIO_toggled.lamp) {
        GPIO_toggled.lamp = 0;
    }

    if (!gpio.reset.held && GPIO_toggled.reset) {
        GPIO_toggled.reset = 0;
    }

    if (!gpio.hour.held && GPIO_toggled.hour) {
        GPIO_toggled.hour = 0;
    }

    if (!gpio.minute.held && GPIO_toggled.minute) {
        GPIO_toggled.minute = 0;
    }
}

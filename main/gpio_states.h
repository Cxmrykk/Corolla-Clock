#ifndef GPIO_STATES_H
#define GPIO_STATES_H

    #include <stdint.h>

    // extension board IO
    #define GPIO_LAMP GPIO_NUM_42
    #define GPIO_ACC GPIO_NUM_43
    #define GPIO_RESET GPIO_NUM_44
    #define GPIO_HOUR GPIO_NUM_45
    #define GPIO_MINUTE GPIO_NUM_46

    // maximum loop cycles to register GPIO event (prevents noise)
    #define GPIO_HOLD_COUNT 2

    typedef struct {
        bool held;
        bool pressed;
    } GPIO_kind_t;

    typedef struct {
        GPIO_kind_t accessory;
        GPIO_kind_t lamp;
        GPIO_kind_t reset;
        GPIO_kind_t hour;
        GPIO_kind_t minute;
    } GPIO_t;

    typedef struct {
        bool accessory;
        bool lamp;
        bool reset;
        bool hour;
        bool minute;
    } GPIO_state_t;

    typedef struct {
        uint8_t accessory;
        uint8_t lamp;
        uint8_t reset;
        uint8_t hour;
        uint8_t minute;
    } GPIO_cycle_t;

    inline GPIO_t gpio = {
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0}
    };

    inline GPIO_state_t GPIO_toggled = { 0, 0, 0, 0, 0 };
    inline GPIO_state_t GPIO_active = { 0, 0, 0, 0, 0 };
    inline GPIO_cycle_t GPIO_cycle = { 0, 0, 0, 0, 0 };

    void get_GPIO_states();

#endif
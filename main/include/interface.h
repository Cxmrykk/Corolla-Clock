#ifndef INTERFACE_H
#define INTERFACE_H

    #include "clock.h"

    void set_clock_time_default(Clock_State_t *state);
    void set_horizontal_alignment(Clock_State_t *state);
    void set_vertical_alignment(Clock_State_t *state);
    void set_brightness(Clock_State_t *state);
    void set_color(Clock_State_t *state);
    void set_background_opacity(Clock_State_t *state);
    void set_clock_size(Clock_State_t *state);
    void set_clock_thickness(Clock_State_t *state);
    void set_clock_padding(Clock_State_t *state);

    typedef void (*Interface_Handler_t)(Clock_State_t*);

    static Interface_Handler_t clock_functions[] = {
        set_clock_time_default,
        set_horizontal_alignment,
        set_vertical_alignment,
        set_brightness,
        set_color,
        set_background_opacity,
        set_clock_size,
        set_clock_thickness,
        set_clock_padding
    };

    static const char* clock_functions_text[][3] = {
    {
        "Set Time",
        "H: Set hour",
        "M: Set minute"
    },
    {
        "Set Horizontal Alignment",
        "H: Move display left",
        "M: Move display right"
    },
    {
        "Set Vertical Alignment",
        "H: Move display up",
        "M: Move display down"
    },
    {
        "Set Brightness",
        "H: Increase brightness",
        "M: Decrease brightness"
    },
    {
        "Set Colour",
        "H: Set Hue",
        "M: Set Brightness"
    },
    {
        "Set Opacity",
        "H: Increase Opacity",
        "M: Decrease Opacity"
    },
    {
        "Set Clock Size",
        "H: Increase Size",
        "M: Decrease Size"
    },
    {
        "Set Clock Thickness",
        "H: Increase Thickness",
        "M: Decrease Thickness"
    },
    {
        "Set Clock Padding",
        "H: Increase Padding",
        "M: Decrease Padding"
    }
};

#endif

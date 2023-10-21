idf_component_register(
    SRCS "main.cpp" "gpio_states.h" "gpio_states.cpp" "rgb565.h" "rgb565.cpp" "driver/pins_config.h" "driver/rm67162.h" "driver/rm67162.cpp" "sprites/digital_num.cpp" "sprites/digital_num.h" "sprites/digital_clock.h" "sprites/digital_clock.cpp"
    INCLUDE_DIRS "." "sprites"
)
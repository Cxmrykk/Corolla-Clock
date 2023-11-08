idf_component_register(
    SRCS "src/main.cpp"
         "src/clock.cpp"
         "src/interface.cpp"
         "src/drivers/gpio_states.cpp"
         "src/drivers/rm67162.cpp"
         "src/sprites/digital_clock.cpp"
         "src/sprites/digital_num.cpp"
         "src/sprites/text_display.cpp"
         "src/sprites/tools/rgb565.cpp"
    INCLUDE_DIRS "include"
)

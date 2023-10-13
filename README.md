### Requirements
- **ESP-IDF** <= v4.4.6
- **Arduino-ESP32** <= v2.0.14 *(Place inside components folder)*
- **TFT-eSPI** <= v2.5.31 *(Place inside components folder)*
- **Required Libraries** (See [Official ESP-IDF Installation Steps](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html))
    - Additionally: `python3-virtualenv`

### Configuration
- **menuconfig** *(Type "menuconfig" in Command Palette)*
    - Set all `TFT_eSPI` driver configuration pins to 0 (we are using `rm67162.h` and `rm67162.cpp` for driving the display)
    - `"Autostart Arduino setup and loop on boot"` should be enabled
- **CMakeLists.txt**
    - Make sure `main.cpp` and `rm67162.cpp` are both in `SRCS` entry for `idf_component_register`
    - `INCLUDE_DIRS` should be set to `"."` (Relative path of `main` directory, includes the header files)
- **VSCode (ESP-IDF)**
    - Set device to `esp32s3`
    - Set flash method to `JTAG`

### Notes
- `TFT-eSPI` is only being used to draw the components, `rm67162.cpp` will set the screen contents
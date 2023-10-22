<h1 align=center>Toyota Corolla AMOLED Clock</h1>
<p align=center>Custom clock project using the LilyGo T-Display-S3 AMOLED</p>

### Features
- Shows the time (hours, minutes, seconds)
- Colour Configuration (hue, white level, opacity)
- Size Configuration (scale, thickness, padding)
- Different graphic profiles based on interior lighting (headlights)
- Screen turns off when accessory off (use buttons to wake)
- Dynamic Brightness

### Dependencies
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
    - Set flash method to `UART`

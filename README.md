<h1 align=center>Toyota Corolla AMOLED Clock</h1>
<p align=center>Custom clock project using the LilyGo T-Display-S3 AMOLED</p>

<div align=center>
    <img src="assets/pcb_model.png">
</div>

### Features
- Display the time on a high resolution AMOLED display
- Different colour/brightness based on interior lighting state (on/off)
- Colour Settings (digit colour, background opacity, whiteness level)
- Size Settings (width, thickness, padding)
- Automatic display timeout when accessory is off

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

### DIY tutorial (step by step)
> Your clock will need 3 buttons (Asia/Pacific Model) otherwise you will need to purchase a separate clock housing for this project.<br>
> You will need a Linux-based OS to flash the software **(Recommended: Debian Desktop or Ubuntu)**

1. **Purchase T-Display-S3 AMOLED + Materials**
    - **T-Display-S3 Amoled** (https://www.lilygo.cc/products/t-display-s3-amoled)
    - Wire cutters
    - Soldering iron
    - Solder
    - Heat resistant cables (thin enough for 2.54mm spaced pins)

2. **Order PCB using JLCPCB service**
    - Create an account on https://jlcpcb.com/
    - Go to https://cart.jlcpcb.com/quote/Upload and upload gerber file in `/docs/schematics`
    - Check "PCB Assembly"
    - Continue checkout process and provide files located in `docs/schematics`.

3. **Order 3D print using JLC3DP service**
    - Login using the same account
    - Repeat this process for both models:
        - Go to https://jlc3dp.com/3d-printing-quote and upload stl file in `/docs/models`
        - Select material of your choice **(make sure it can withstand hot temperatures!!!)**
        - Add to cart, proceed with checkout process

4. **Flashing the Software**
    - Download Visual Studio Code (https://code.visualstudio.com)
    - Install dependencies as specified above in README
    - Reproduce configuration steps as specified above in README
        - Clone the project: `git clone https://github.com/Cxmrykk/Corolla-Clock.git`
        - Enter project directory: `cd Corolla-Clock`
        - Open with VSCode: `code .`
    - Connect the T-Display-S3 AMOLED board via USB-C and click the "Flash" button at the bottom

4. **Soldering Process**
    - Trim the wires on both sides (around 0.5cm) and tin them using soldering iron (makes it easier to solder)
    - Solder wires to the T-Display-S3 AMOLED pins
        - GPIO 42: LAMP
        - GPIO 43: ACCESSORY
        - GPIO 44: RESET
        - GPIO 45: HOUR
        - GPIO 46: MINUTE
        - VBUS: VCC
        - 3.3V: 3.3V
        - GND: GND
    - After they are soldered, trim the ends off so that they don't touch<br>(on the top of the board, not the cables)
    - Solder the other side of the cables to the PCB (use the pin map above)
    - Double check all pins are soldered and none of them are touching

5. **Clock Removal & Assembly**
    - Take out the clock by following a tutorial on youtube
    - Disassemble the clock by following a tutorial on youtube (Be careful, the clock housing clips are brittle)
    - Empty the existing buttons, take out the existing circuit board.
    - Attach the new PCB to the clock housing (use the existing screw to secure it in place)
    - Insert the 3D printed mount and buttons (the mount will need some force to shove it in properly)
    - Insert the Screen and PCB:
        - The USB-C port should be on the right side. LILYGO logo should be upright (same orientation as clock housing)
        - Insert the screen first, then clip in the rest of the housing (with the PCB attached)
    - Finally, put the clock back in and put everything back together in your car.

7. **Changing Alignment and Time**
    - Press the reset button (`:00`) to toggle the mode overlay.
    - Press the hour button twice (`H`) to cycle to the vertical positioning menu.
    - Press the reset button once more and hold the `H` and `M` buttons to move the screen up/down.
    - Adjust screen position as required. You should be able to read the text now.
    - Configure your clock as required (Set time, align screen, colours, sizing, brightness, etc)
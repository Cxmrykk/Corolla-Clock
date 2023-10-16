# TFT_eSprite Class Documentation

The `TFT_eSprite` class is a C++ class designed to create and manipulate sprites in RAM that can be used for efficient graphics rendering on TFT screens. It is a subclass of the `TFT_eSPI` class and inherits graphics functions from it. This class is particularly useful for creating and rendering graphics on TFT displays. 

## Constructor

### `explicit TFT_eSprite(TFT_eSPI *tft)`
- Constructor for the `TFT_eSprite` class. It takes a pointer to an instance of the `TFT_eSPI` class as a parameter and initializes a sprite.

## Destructor

### `~TFT_eSprite(void)`
- Destructor for the `TFT_eSprite` class. Deallocates memory used by the sprite.

## Sprite Creation

### `void* createSprite(int16_t width, int16_t height, uint8_t frames = 1)`
- Creates a sprite with the specified width, height, and number of frames. Returns a pointer to the RAM area used by the sprite.

### `void* getPointer(void)`
- Returns a pointer to the sprite's memory. Returns `nullptr` if the sprite has not been created.

### `bool created(void)`
- Checks if a sprite has been created and returns `true` if it has.

### `void deleteSprite(void)`
- Deletes the sprite and frees up the RAM used by it.

## Frame Buffer Selection

### `void* frameBuffer(int8_t f)`
- Selects the frame buffer for graphics write. Returns a pointer to the sprite's frame buffer.

## Color Depth

### `void* setColorDepth(int8_t b)`
- Sets the color depth of the sprite to 1, 4, 8, or 16 bits. Returns a new pointer to the sprite if it's re-created with the new depth.

### `int8_t getColorDepth(void)`
- Returns the current color depth of the sprite.

## Palette

### `void createPalette(uint16_t *palette = nullptr, uint8_t colors = 16)`
- Sets the palette for a 4-bit depth sprite. The palette is an array of 16 colors, and only the first 16 colors in the map are used.

### `void createPalette(const uint16_t *palette = nullptr, uint8_t colors = 16)`
- Sets the palette for a 4-bit depth sprite from flash memory.

### `void setPaletteColor(uint8_t index, uint16_t color)`
- Sets the color for a specific index in the palette.

### `uint16_t getPaletteColor(uint8_t index)`
- Retrieves the color at the specified palette index.

## Graphics Drawing

### `void drawPixel(int32_t x, int32_t y, uint32_t color)`
- Draws a single pixel at the specified x and y coordinates with the given color.

### `void drawChar(int32_t x, int32_t y, uint16_t c, uint32_t color, uint32_t bg, uint8_t size)`
- Draws a single character in the GLCD or GFXFF font.

### `void fillSprite(uint32_t color)`
- Fills the entire sprite with the specified color.

### `void setWindow(int32_t x0, int32_t y0, int32_t x1, int32_t y1)`
- Defines a window in the sprite for drawing, which is used for subsequent graphics operations within the defined area.

### `void pushColor(uint16_t color)`
- Pushes a single color (pixel) to the sprite's set window area.

### `void pushColor(uint16_t color, uint32_t len)`
- Pushes multiple colors (pixels) to the sprite's set window area.

### `void writeColor(uint16_t color)`
- Pushes a pre-formatted pixel with 1, 4, 8, or 16-bit color depth to the sprite's set window area.

### `void drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)`
- Draws a line between two points with the specified color.

### `void drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color)`
- Draws a vertical line with the specified color.

### `void drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color)`
- Draws a horizontal line with the specified color.

### `void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)`
- Fills a rectangular area with the specified color, effectively drawing a filled rectangle.

## Sprite Rotation

### `void setRotation(uint8_t rotation)`
- Sets the coordinate rotation of the sprite. This is primarily for 1-bit per pixel sprites and is used for ePaper displays.

### `uint8_t getRotation(void)`
- Returns the current sprite rotation setting.

### `bool pushRotated(int16_t angle, uint32_t transp = 0x00FFFFFF)`
- Pushes a rotated copy of the sprite to the TFT screen with an optional transparent color.

### `bool pushRotated(TFT_eSprite *spr, int16_t angle, uint32_t transp = 0x00FFFFFF)`
- Pushes a rotated copy of the sprite to another different sprite with an optional transparent color.

### `bool getRotatedBounds(int16_t angle, int16_t *min_x, int16_t *min_y, int16_t *max_x, int16_t *max_y)`
- Retrieves the bounding box for a rotated copy of the sprite.

### `bool getRotatedBounds(TFT_eSprite *spr, int16_t angle, int16_t *min_x, int16_t *min_y, int16_t *max_x, int16_t *max_y)`
- Retrieves the destination sprite's bounding box for a rotated copy of this sprite.

## Miscellaneous Functions

### `uint16_t readPixel(int32_t x0, int32_t y0)`
- Reads the color of a pixel at the specified coordinates and returns the value in 565 format.

### `uint16_t readPixelValue(int32_t x, int32_t y)`
- Returns the numerical value of the pixel at the specified coordinates.

### `void pushImage(int32_t x0, int32_t y0, int32_t w, int32_t h, uint16_t *data, uint8_t sbpp = 0)`
- Writes an image (color bitmap) to the sprite.

### `void pushImage(int32_t x0, int32_t y0, int32_t w, int32_t h, const uint16_t *data)`
- Writes an image (color bitmap) to the sprite from flash memory.

### `void pushSprite(int32_t x, int32_t y)`
- Pushes the sprite to the TFT screen. Optionally, a transparent color can be defined to exclude certain pixels from rendering.

### `void pushSprite(int32_t x, int32_t y, uint16_t transparent)`
- Pushes the sprite to the TFT screen with an optional transparent color.

### `bool pushSprite(int32_t tx, int32_t ty, int32_t sx, int32_t sy, int32_t sw, int32_t sh)`
- Pushes a windowed area of

 the sprite to the TFT at specified coordinates.

### `bool pushToSprite(TFT_eSprite *dspr, int32_t x, int32_t y)`
- Pushes the sprite to another sprite at the specified coordinates.

### `bool pushToSprite(TFT_eSprite *dspr, int32_t x, int32_t y, uint16_t transparent)`
- Pushes the sprite to another sprite at the specified coordinates with an optional transparent color.

### `int16_t drawChar(uint16_t uniCode, int32_t x, int32_t y, uint8_t font)`
- Draws a single character using the loaded font at the specified position.

### `int16_t drawChar(uint16_t uniCode, int32_t x, int32_t y)`
- Draws a single character using the loaded font at the specified position.

### `int16_t width(void)`
- Returns the width of the sprite.

### `int16_t height(void)`
- Returns the height of the sprite.

## Anti-Aliased Fonts (Associated Functions)

These functions are associated with anti-aliased fonts:

### `void drawGlyph(uint16_t code)`
- Draws a single Unicode character using the loaded font.

### `void printToSprite(String string)`
- Prints a string to the sprite using the loaded font at the cursor position.

### `void printToSprite(char *cbuffer, uint16_t len)`
- Prints a character array to the sprite using the loaded font at the cursor position.

### `int16_t printToSprite(int16_t x, int16_t y, uint16_t index)`
- Prints an indexed glyph to the sprite using the loaded font at the specified coordinates.

## Private Members

- `_tft`: Pointer to an instance of the `TFT_eSPI` class.

## Protected Members

These members are accessible by derived classes:

- `_bpp`: Bits per pixel (1, 4, 8, or 16).
- `_img`: Pointer to a 16-bit sprite.
- `_img8`: Pointer to 1 and 8-bit sprite frame 1 or frame 2.
- `_img4`: Pointer to a 4-bit sprite (uses a color map).
- `_img8_1`: Pointer to frame 1.
- `_img8_2`: Pointer to frame 2.
- `_colorMap`: Color map pointer (16 entries, used with 4-bit color map).
- `_sinra`: Sine of the rotation angle in fixed point.
- `_cosra`: Cosine of the rotation angle in fixed point.
- `_created`: Indicates whether a sprite has been created and memory reserved.
- `_gFont`: Indicates if an anti-aliased font is loaded.
- `_xs`, `_ys`, `_xe`, `_ye`, `_xptr`, `_yptr`: Used for `setWindow`.
- `_sx`, `_sy`, `_sw`, `_sh`, `_scolor`: Used for scrolling.
- `_iwidth`, `_iheight`: Sprite memory image bit width and height (swapped during rotations).
- `_dwidth`, `_dheight`: Real sprite width and height (for <8bpp sprites).
- `_bitwidth`: Sprite image bit width for `drawPixel` (for <8bpp sprites, not swapped).

This class provides a wide range of functionality for creating and manipulating sprites in RAM, making it useful for graphics applications on TFT displays.
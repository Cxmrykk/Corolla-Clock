# TFT_eSPI Documentation

The `TFT_eSPI` class provides a range of functions for controlling TFT displays. Below are the key functions and their descriptions:

## Constructor

### `TFT_eSPI(int16_t _W = TFT_WIDTH, int16_t _H = TFT_HEIGHT)`

Initialize a TFT display object with the specified width and height.

## Pixel Drawing

- `drawPixel(int32_t x, int32_t y, uint32_t color)`: Draw a single pixel at the specified coordinates with the given color.
- `drawChar(int32_t x, int32_t y, uint16_t c, uint32_t color, uint32_t bg, uint8_t size)`: Draw a character at the specified position with color and background color.
- `drawLine(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint32_t color)`: Draw a line between two points with the specified color.
- `drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color)`: Draw a vertical line with a given height and color.
- `drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color)`: Draw a horizontal line with a given width and color.
- `fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)`: Fill a rectangular area with the specified color.

## Character and Text Information

- `int16_t drawChar(uint16_t uniCode, int32_t x, int32_t y, uint8_t font)`: Draw a character specified by Unicode at the given position using a specific font.
- `int16_t drawChar(uint16_t uniCode, int32_t x, int32_t y)`: Draw a character at the given position using the current font.
- `int16_t height(void)`: Get the height of the current font.
- `int16_t width(void)`: Get the width of the current font.

## Reading Pixel Color

- `uint16_t readPixel(int32_t x, int32_t y)`: Read the color of a pixel at the specified coordinates in 565 format.

## Window and Display Control

- `void setWindow(int32_t xs, int32_t ys, int32_t xe, int32_t ye)`: Set the active window on the display.
- `void pushColor(uint16_t color)`: Push (write) pixel colors to the active window.
- `void begin_nin_write()`: Start writing pixel data to the display.
- `void end_nin_write()`: End writing pixel data to the display.
- `void setRotation(uint8_t r)`: Set the display rotation to 0, 1, 2, or 3.
- `uint8_t getRotation(void)`: Read the current display rotation.
- `void setOrigin(int32_t x, int32_t y)`: Change the display origin position.
- `int32_t getOriginX(void)`: Get the X coordinate of the display origin.
- `int32_t getOriginY(void)`: Get the Y coordinate of the display origin.
- `void invertDisplay(bool i)`: Invert all displayed colors on the TFT.

## Viewport and Clipping

- `void setAddrWindow(int32_t xs, int32_t ys, int32_t w, int32_t h)`: Set the active window using coordinates and size.
- `void setViewport(int32_t x, int32_t y, int32_t w, int32_t h, bool vpDatum = true)`: Set a viewport with specified position and size.
- `bool checkViewport(int32_t x, int32_t y, int32_t w, int32_t h)`: Check if a specified area is within the viewport bounds.
- `int32_t getViewportX(void)`: Get the X coordinate of the viewport.
- `int32_t getViewportY(void)`: Get the Y coordinate of the viewport.
- `int32_t getViewportWidth(void)`: Get the width of the viewport.
- `int32_t getViewportHeight(void)`: Get the height of the viewport.
- `bool getViewportDatum(void)`: Get the viewport datum flag.
- `void frameViewport(uint16_t color, int32_t w)`: Create a border around the viewport.
- `void resetViewport(void)`: Reset the viewport to the top-left corner.

## Clipping Functions

- `bool clipAddrWindow(int32_t* x, int32_t* y, int32_t* w, int32_t* h)`: Clip a window area to the viewport bounds.
- `bool clipWindow(int32_t* xs, int32_t* ys, int32_t* xe, int32_t* ye)`: Clip a window to the viewport bounds.

## Graphics Drawing

- `void fillScreen(uint32_t color)`: Fill the entire screen with the specified color.
- `void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)`: Draw a rectangle with the specified size and color.
- `void drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color)`: Draw a rounded rectangle with the specified parameters.
- `void fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color)`: Fill a rounded rectangle with the specified parameters.
- `void fillRectVGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color1, uint32_t color2)`: Fill a vertical gradient rectangle.
- `void fillRectHGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color1, uint32_t color2)`: Fill a horizontal gradient rectangle.
- `void drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color)`: Draw a circle with the specified radius and color.
- `void drawCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, uint32_t color)`: Draw a circle corner with the specified parameters.
- `void fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color)`: Fill a circle with the specified radius and color.
- `void fillCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, int32_t delta, uint32_t color)`: Fill a circle corner with the specified parameters.
- `void drawEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color)`: Draw an ellipse with the specified parameters.
- `void fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color)`: Fill an ellipse with the specified parameters.
- `void drawTriangle(int32_t x1,int32_t y1, int32_t x2,int32_t y2, int32_t x3,int32_t y3, uint32_t color)`: Draw a triangle with three specified points and a color.
- `void fillTriangle(int32_t x1,int32_t y1, int32_t x2,int32_t y2, int32_t x3,int32_t y3, uint32_t color)`: Fill a triangle with three specified points and a color.

## Smooth Graphics Drawing

- `uint16_t drawPixel(int32_t x, int32_t y, uint32_t color, uint8_t alpha, uint32_t bg_color = 0x00FFFFFF)`: Draw a pixel with alpha blending.
- `void drawSmoothArc(int32_t x, int32_t y, int32_t r, int32_t ir, uint32_t startAngle, uint32_t endAngle, uint32_t fg_color, uint32_t bg_color, bool roundEnds = false)`: Draw a smooth arc.
- `void drawArc(int32_t x, int32_t y, int32_t r, int32_t ir, uint32_t startAngle, uint32_t endAngle, uint32_t fg_color, uint32_t bg_color, bool smoothArc = true)`: Draw an arc.
- `void drawSmoothCircle(int32_t x, int32_t y, int32_t r, uint32_t fg_color, uint32_t bg_color)`: Draw a smooth circle.
- `void drawSmoothRoundRect(int32_t x, int32_t y, int32_t r, int32_t ir, int32_t w, int32_t h, uint32_t fg_color, uint32_t bg_color = 0x00FFFFFF, uint8_t quadrants = 0xF)`: Draw a smooth rounded rectangle.
- `void fillSmoothRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color, uint32_t bg_color = 0x00FFFFFF)`: Fill a smooth rounded rectangle.
- `void drawSpot(float ax, float ay, float r, uint32_t fg_color, uint32_t bg_color = 0x00FFFFFF)`: Draw a spot with a specified radius.
- `void drawWideLine(float ax, float ay, float bx, float by, float wd, uint32_t fg_color, uint32_t bg_color = 0x00FFFFFF)`: Draw a wide line.
- `void drawWedgeLine(float ax, float ay, float bx, float by, float aw, float bw, uint32_t fg_color, uint32_t bg_color = 0x00FFFFFF)`: Draw a wedge line.

## Image Rendering

- `void setSwapBytes(bool swap)`: Swap the byte order for image rendering functions.
- `bool getSwapBytes(void)`: Get the current byte swap setting.
- `void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t fgcolor)`: Draw a bitmap image.
- `void drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t fgcolor)`: Draw an XBitmap image.
- `void setBitmapColor(uint16_t fgcolor, uint16_t bgcolor)`: Set the colors for 1bpp sprites.
- `void setPivot(int16_t x, int16_t y)`: Set the pivot point for rendering rotated sprites.
- `int16_t getPivotX(void)`: Get the X coordinate of the pivot point.
- `int16_t getPivotY(void)`: Get the Y coordinate of the pivot point.

## Copy Screen Blocks

- `void readRect(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data)`: Read a block of pixels to a data buffer.
- `void pushRect(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data)`: Write a block of pixels to the screen.

## Image Rendering from RAM and FLASH

- `void pushImage(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data)`: Render an image from RAM.
- `void pushImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint16_t *data)`: Render an image from FLASH.
- `void pushImage(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t *data, bool bpp8 = true, uint16_t *cmap = nullptr)`: Render an image from RAM with 1, 4, or 8 bits per pixel.
- `void pushImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint8_t *data, bool bpp8, uint16_t *cmap = nullptr)`: Render an image from FLASH with 1, 4, or 8 bits per pixel.
- `void pushMaskedImage(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *img, uint8_t *mask)`: Render an image with a 1bpp mask.

## Text Rendering

- `int16_t drawNumber(long intNumber, int32_t x, int32_t y, uint8_t font)`: Draw an integer using a specific font.
- `int16_t drawNumber(long intNumber, int32_t x, int32_t y)`: Draw an integer using the current font.
- `int16_t drawFloat(float floatNumber, uint8_t decimal, int32_t x, int32_t y, uint8_t font)`: Draw a floating-point number using a specific font and a specified number of decimal places.
- `int16_t drawFloat(float floatNumber, uint8_t decimal, int32_t x, int32_t y)`: Draw a floating-point number using the current font and a specified number of decimal places.
- `int16_t drawString(const char *string, int32_t x, int32_t y, uint8_t font)`: Draw a string using a specific font.
- `int16_t drawString(const char *string, int32_t x, int32_t y)`: Draw a string using the current font.
- `int16_t drawString(const String& string, int32_t x, int32_t y, uint8_t font)`: Draw a string using a specific font.
- `int16_t drawString(const String& string, int32_t x, int32_t y)`: Draw a string using the current font.

## Text Rendering and Font Handling Support

- `void setCursor(int16_t x, int16_t y)`: Set the cursor for text printing.
- `void setCursor(int16_t x, int16_t y, uint8_t font)`: Set the cursor and font number for text printing.
- `int16_t getCursorX(void)`: Get the current cursor X position.
- `int16_t getCursorY(void)`: Get the current cursor Y position.
- `void setTextColor(uint16_t color)`: Set the character (glyph) color only.
- `void setTextColor(uint16_t fgcolor, uint16_t bgcolor, bool bgfill = false)`: Set the character (glyph) foreground and background color.
- `void setTextSize(uint8_t size)`: Set the character size multiplier.
- `void setTextWrap(bool wrapX, bool wrapY = false)`: Turn on/off text wrapping.
- `void setTextDatum(uint8_t datum)`: Set text datum position.
- `uint8_t getTextDatum(void)`: Get the text datum.
- `void setTextPadding(uint16_t x_width)`: Set text padding (background blanking/over-write) width in pixels.
- `uint16_t getTextPadding(void)`: Get the text padding.

## Colour Conversion and Alpha Blending

- `uint16_t color565(uint8_t red, uint8_t green, uint8_t blue)`: Convert 8-bit red, green, and blue to 16-bit color.
- `uint16_t color8to16(uint8_t color332)`: Convert 8-bit color to 16-bit color.
- `uint8_t color16to8(uint16_t color565)`: Convert 16-bit color to 8-bit color.
- `uint32_t color16to24(uint16_t color565)`: Convert 16-bit color to 24-bit color.
- `uint32_t color24to16(uint32_t color888)`: Convert 24-bit color to 16-bit color.
- `uint16_t alphaBlend(uint8_t alpha, uint16_t fgc, uint16_t bgc)`: Alpha blend two colors.
- `uint16_t alphaBlend(uint8_t alpha, uint16_t fgc, uint16_t bgc, uint8_t dither)`: Alpha blend two colors with dithering.
- `uint32_t alphaBlend24(uint8_t alpha, uint32_t fgc, uint32_t bgc, uint8_t dither = 0)`: Alpha blend two 24-bit colors with optional alpha dither.

## Other Functions

- `uint32_t textcolor, textbgcolor`: Text foreground and background colors.
- `uint32_t bitmap_fg, bitmap_bg`: Bitmap foreground (bit=1) and background (bit=0) colors.
- `uint8_t textfont, textsize, textdatum, rotation`: Current font, size, text datum, and display rotation settings.
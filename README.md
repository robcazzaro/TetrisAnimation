# TetrisAnimation

An Arduino library for drawing letters and numbers using a falling block style animation.

[![alt text](https://github.com/robcazzaro/TetrisTFTAnimation/blob/master/TetrisDemo.gif "Tetris alphabet animation")]

Original library by Tobias Blum https://github.com/toblum/TetrisAnimation

Desigined orginally for RGB LED Matrixes, modified to work with SPI TFT screen and https://github.com/Bodmer/TFT_eSPI.

Main improvements include adding 3D border effects to blocks when scaled up, having the block start from random starting points and move towards the final destination, fixing a rotation bug in the original library (the logic recognized only 0 and 1 rotations, even if the characters were designed for up to 3 rotations.)

Demo and all test done on an integrated ESP32 and TFT board: https://github.com/Xinyuan-LilyGO/TTGO-T-Display.  The library should still work with the original Adafruit GFX library and the original samples should still work, but not guaranteed

### Displays/Libraries tested (Examples included)

- Integrated ESP32 and TFT https://github.com/Xinyuan-LilyGO/TTGO-T-Display  [TFT_eSPI ESP32/ESP8266 library](https://github.com/Bodmer/TFT_eSPI)

Original libraries, not tested with updated library, but should still work
- RGB LED Matrix using the [PxMatrix library](https://github.com/2dom/PxMatrix/) - ESP8266 and ESP32
- VGA Display using the [Bitluni ESP32Lib](https://github.com/bitluni/ESP32Lib) - ESP32
- Nokia 5110 Screen using a modified [Adafruit PCD8544 library](https://github.com/bbx10/Adafruit-PCD8544-Nokia-5110-LCD-library/tree/esp8266) - ESP8266


## Installation & Setup

From ZIP file

## Basic Usage

See example for more details.

### Intialise library by passing in a display:

```
TFT_eSPI tft = TFT_eSPI(135, 240);		// create an instance of TFT_eSPI screen
TetrisTFTDraw tetris(tft); //Pass it into the library

```

### Set the value:

Set the value of the library by using one of: setTime, setNumbers or setText commands

```
// Usage: setTime(time_string, forceRefresh = false)
// time_string = time in the format "21:23"
// forceRefresh: by default, a digit will only redraw if it's value has changed
//               (so for a clock the hour digit would only draw once an hour)
//               but setting this value to true tells the library to redraw
//               all the digits.  
tetris.setTime("12:34");

// Usage: setNumbers(num, forceRefresh = false)
// num = Integer value. Max: 999999999 (9 digits long) Min: 0 (negative not currently supported).
// forceRefresh: by default, a digit will only redraw if it's value has changed
//               (so for a clock the hour digit would only draw once an hour)
//               but setting this value to true tells the library to redraw
//               all the digits.  
tetris.setNumbers(1234);

// Usage: setText(string, forceRefresh = false)
// string = regular text string, Use uppercase letters only.
// forceRefresh: by default, a digit will only redraw if it's value has changed
//               (so for a clock the hour digit would only draw once an hour)
//               but setting this value to true tells the library to redraw
//               all the digits.
//
// For full list of characters supported, check the AlphaTest examples.
tetris.setText("HOWDY!");

```

### Draw the value:

These will normally be called in a timer or ticker (see the example). How often they are called will increase/decrease the speed of which the blocks drop.

```

// Usage: drawNumbers(x, y, showColon) (for use with setTime or setNumber)
// x = most left Pixel of the text 
// y = The bottom of the number when it lands, they will start falling from y + (16 * scale)
// showColon = (optional) show the colon or not, defaults to false (only applicaple when using setTime)
//
// Returns a boolean to indicate if its finished animating
// (will return false if there is still falling blocks)
tetris.drawNumbers(16,8, true);

// Usage: drawText(x, y) (for use with setText)
// x = most left Pixel of the text 
// y = The bottom of the text when it lands, they will start falling from y + (16 * scale)
//
// Returns a boolean to indicate if its finished animating
// (will return false if there is still falling blocks)
tetris.drawText(16,8);

```

### Scale the font:

```
// Usage: scale = 2
// Will scale up the size of the characters
// Can be used with either numbers or text 

tetris.scale = 2; // must be called before setText, setTime or setNumbers
tetris.setText("BIG"); // This will be twice the size as normal
delay(5000);
tetris.setText("STILL BIG"); // scale persists
delay(5000);
tetris.scale = 1; // can be reset to normal size if required
tetris.setText("SMALL");
```

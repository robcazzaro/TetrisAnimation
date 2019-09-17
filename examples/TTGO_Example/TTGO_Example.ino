/********************************************************************
*    Example showing writing text using the TetrisAnimation         *
*    library on a TTGO-T-Display ESP32 board                        *
*    https://github.com/Xinyuan-LilyGO/TTGO-T-Display               *
*                                                                   *
*                                                                   *
*    Written by Roberto Cazzaro (Robcazzaro on Github)              *
*    https://github.com/robcazzaro/TetrisAnimation                  *
*                                                                   *
*    Based on https://github.com/toblum/TetrisAnimation             *
*********************************************************************/


#include <TFT_eSPI.h>   https://github.com/Bodmer/TFT_eSPI with TTGO-T-Display header https://github.com/Xinyuan-LilyGO/TTGO-T-Display/blob/master/TTGO_T_Display.h
#include <SPI.h>    // ESP32 library
#include <Ticker.h>   // ESP32 library
#include <TetrisTFTDraw.h>

#ifndef TFT_DISPOFF
#define TFT_DISPOFF 0x28
#endif

#ifndef TFT_SLPIN
#define TFT_SLPIN   0x10
#endif

#define TFT_MOSI            19
#define TFT_SCLK            18
#define TFT_CS              5
#define TFT_DC              16
#define TFT_RST             23
#define TFT_BL          4  // Display backlight control pin

#define DISPLAY_LIBRARY TFT_ESPI

#define TETRIS_SCALE_CLOCK  8
#define TETRIS_SCALE_LETTERS  5

TFT_eSPI tft = TFT_eSPI(135, 240);
Ticker animationTicker;
boolean animate;
boolean pulseOn;
boolean updateNTP;
double animationTick = 0.15;    // default interval between drops in seconds
int tftBacklight = 205;      // backlight PWM 0-255
TFT_eSprite img = TFT_eSprite(&tft);    // using a Sprite to avoid flickering (double buffering technique)
TetrisTFTDraw tetris(img);


void animationHandlerClock()
{
    if (animate) 
    {
      img.fillSprite(TFT_BLACK);
      animate = !tetris.drawNumbers(0, 125, true);
      img.pushSprite(0, 0);
    }
}


void animationHandlerLetters()
{
    if (animate) 
    {
      img.fillSprite(TFT_BLACK);
      animate = !tetris.drawText(0, 125);
      img.pushSprite(0, 0);
    }
}


void setup()
{
    Serial.begin(115200);
    Serial.println("Start");
    
    tft.init();
    tft.setRotation(1);

    // Set backlight intensity using PWM output
    ledcSetup(1, 1000, 8);   // PWM channel 1, 1000Hz, 8 bit
    ledcAttachPin(TFT_BL, 1);   // attach to TFT backlight
    ledcWrite(1, tftBacklight); // set backlight

    // use a sprite as double buffer to animate screen with no flickering
    // frame is drawn on the sprite, then the sprite (with black backround) is 
    // overimposed on the TFT screen, erasing previous content at the same time
    img.createSprite(240, 135);
    img.fillSprite(TFT_BLACK);

    yield();
    tft.fillScreen(TFT_BLACK);  // Clear TFT
}


void loop()
{
    // Tetris blocks visual effects
    tetris.scale = TETRIS_SCALE_CLOCK;
    tetris.drawOutline = false;
    tetris.drawBlockOutline = false;
    tetris.draw3DOutline = true;      //3D outline effect
    tetris.draw3DDblOutline = false;

    animationTicker.attach(animationTick, animationHandlerClock);   // set animation handler for numbers, a clock in this case
    tetris.setRandomDropStart();    // set random start point for each tetromino in each digit
    tetris.setTime("10:38", false);     // demo time
    animate = true;
    do {
      delay(1);
    } while (animate);    // wait until animation completes
    delay(1000);          // plus one second
    tetris.setRandomDropStart();    // set random start point for each tetromino in each digit
    tetris.setTime("10:39", false);   // show how digits change every minute
    animate = true;
    do {
      delay(1);
    } while (animate);    // wait until animation completes
    delay(2000);          // plus two seconds    

    animationTicker.attach(animationTick, animationHandlerLetters);   // switch to animation handler for letters
    tetris.scale = TETRIS_SCALE_LETTERS;
    tetris.setRandomDropStart(); 
    tetris.setText("!#$%&'(");
    animate = true;    
    do {
      delay(1);
    } while (animate);    // wait until animation completes
    delay(2000);          // plus two seconds
    
    tetris.setRandomDropStart(); 
    tetris.setText(")*+,-./");
    animate = true;    
    do {
      delay(1);
    } while (animate);    // wait until animation completes
    delay(2000);          // plus two seconds

    tetris.setRandomDropStart(); 
    tetris.setText("0123456");
    animate = true;    
    do {
      delay(1);
    } while (animate);    // wait until animation completes
    delay(2000);          // plus two seconds

    tetris.setRandomDropStart(); 
    tetris.setText("789:;<=");
    animate = true;    
    do {
      delay(1);
    } while (animate);    // wait until animation completes
    delay(2000);          // plus two seconds

    tetris.setRandomDropStart(); 
    tetris.setText(">?@ABCD");
    animate = true;   
    do {
      delay(1);
    } while (animate);    // wait until animation completes
    delay(2000);          // plus two seconds

    tetris.setRandomDropStart(); 
    tetris.setText("HIJKLMNO");
    animate = true;    
    do {
      delay(1);
    } while (animate);    // wait until animation completes
    delay(2000);          // plus two seconds

    tetris.setRandomDropStart(); 
    tetris.setText("EFGPQRS");
    animate = true;    
    do {
      delay(1);
    } while (animate);    // wait until animation completes
    delay(2000);          // plus two seconds

    tetris.setRandomDropStart(); 
    tetris.setText("TUVWXYZ");
    animate = true;    
    do {
      delay(1);
    } while (animate);    // wait until animation completes
    delay(2000);          // plus two seconds    
}

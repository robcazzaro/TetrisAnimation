/*
Copyright (c) 2019 Roberto Cazzaro . All right reserved.

Tetris TFT library 
Based on https://github.com/toblum/TetrisAnimation, adapted
for TFT screens, 3D block effects and lateral movements

Copyright (c) 2018 Tobias Blum . All right reserved.

Tetris Matrix Clock

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#ifndef TetrisTFTDraw_h
#define TetrisTFTDraw_h

#include <Arduino.h>

// Uses Adafruit GFX library by default unless TFT_ESPI is defined
#if DISPLAY_LIBRARY == TFT_ESPI
  #include "TFT_eSPI.h"
#else
  #include "Adafruit_GFX.h"
#endif

#define TETRIS_MAX_NUMBERS 9

#define TETRIS_DISTANCE_BETWEEN_DIGITS 7
#define TETRIS_Y_DROP_DEFAULT 16

#define TETRIS_RED 0xF800
#define TETRIS_GREEN 0x07E0
#define TETRIS_BLUE 0x001F
#define TETRIS_WHITE 0xEF7D
#define TETRIS_YELLOW 0xFFE0
#define TETRIS_CYAN 0x07FF 
#define TETRIS_MAGENTA 0xA81F
#define TETRIS_ORANGE 0xFD60
#define TETRIS_BLACK 0x0000

// Type that describes the current state of a drawn number
typedef struct
{
  int num_to_draw; // Number to draw (0-9)
  int blockindex;  // The index of the brick (as defined in the falling instructions) that is currently falling
  int fallindex;   // y-position of the brick it already has (incrementing with each step)
  int x_shift;     // x-position of the number relative to the matrix where the number should be placed.
} numstate;

class TetrisTFTDraw
{
    public:
        #if DISPLAY_LIBRARY == TFT_ESPI
		  TetrisTFTDraw (TFT_eSPI  &display);
          TFT_eSPI *display;
		#else
		  TetrisMatrixDraw (Adafruit_GFX  &display);
          Adafruit_GFX  *display;
		#endif
        bool drawNumbers(int x = 0, int y = 0, bool displayColon = false);
        bool drawText(int x = 0, int y = 0);
        void drawChar(String letter, uint8_t x, uint8_t y, uint16_t color);
        void drawShape(int blocktype, uint16_t color, int x_pos, int y_pos, int num_rot);
        void drawLargerShape(int scale, int blocktype, uint16_t color, int x_pos, int y_pos, int num_rot, int borderColorIndex);
        void drawLargerBlock(int x_pos, int y_pos, int scale, uint16_t color, int borderColorIndex);
        void setTime(String time, bool forceRefresh = false);
        void setNumbers(int value, bool forceRefresh = false);
        void setText(String txt, bool forceRefresh = false);
        void setNumState(int index, int value, int x_shift);
        void drawColon(int x, int y, uint16_t colonColour, uint16_t borderColorIndex);
        int calculateWidth();
		void setRandomDropStart();    // set random starting drop point for each tetromino in each number
        bool _debug = false;
        int scale = 1;
        bool drawOutline = false;			// outline fixed color (outLineColour, default = black)
		bool drawBlockOutline = false;		// outline using block border color
		bool draw3DOutline = false;			// single 3D border
		bool draw3DDblOutline = false;		// double 3D border
        uint16_t outLineColour = 0x0000;

        uint16_t tetrisColors[9] = {0xFFE0, 0xF800, 0xFD60, 0xEF7D, 0x07FF,	// Yellow, Red, Orange, White, Cyan
									0x001F, 0xA81F, 0x07E0, 0x0000};		// Blue, Magenta, Green, Black
		uint16_t tetris3DColors[9][3] = {		// 3D effect border colors; top, sides, bottom
										{0xFFF5, 0xBDE0, 0x6320},	// Yellow Square
										{0xFD55, 0xB800, 0x6000},	// Red Z
										{0xFF15, 0xBC00, 0x6200},	// Orange L 
										{0xFFFF, 0xCE79, 0x6B4D},	// White for colon 0xEF7D body color
										{0xAFFF, 0x05F7, 0x032C},	// Cyan I
										{0xAD5F, 0x0017, 0x000C},	// Blue J
										{0xE55F, 0x8017, 0x400C},	// Magenta T
										{0xAFF5, 0x05E0, 0x0320},	// Green S 
										{0x0000, 0x0000, 0x0000}};	// Black
										
		int randomStart[4][13];		// random start for each block in each number/character position								

    private:
        //void intialiseColors();
        void resetNumStates();
        numstate numstates[TETRIS_MAX_NUMBERS];
        int sizeOfValue;
};

#endif
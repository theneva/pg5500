#include "LedControl.h"

#define ROWS_IN_FIGURE 8

/** (I'm a Java developer)
 * pin 12 is connected to the DataIn
 * pin 11 is connected to the CLK
 * pin 10 is connected to LOAD
 */
LedControl lc = LedControl(12, 11, 10, 1);

static const byte space[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
static const byte dot[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00111100,B00111100,B00111100};
static const byte at[]={B00111100,B01100110,B01011010,B01010010,B01011010,B01100110,B00111100,B00000000};
static const byte hash[]={B01100110,B01100110,B11111111,B01100110,B01100110,B11111111,B01100110,B01100110};

static const byte A[]={B00000000,B11111100,B11001110,B11001110,B11111110,B11001110,B11001110,B11001110};
static const byte B[]={B00000000,B11111100,B11001110,B11111100,B11001110,B11001110,B11111110,B11111100};
static const byte C[]={B00000000,B01111100,B11001110,B11000000,B11000000,B11001110,B11111110,B01111100};
static const byte D[]={B00000000,B11111100,B11001110,B11001110,B11001110,B11001110,B11111110,B11111100};
static const byte E[]={B00000000,B01111100,B11000110,B11110000,B11000000,B11001110,B11111110,B01111100};
static const byte F[]={B00000000,B01111110,B11001110,B11000000,B11110000,B11000000,B11000000,B11000000};
static const byte G[]={B00000000,B01111100,B11001110,B11000000,B11011110,B11001110,B11111110,B01111100};
static const byte H[]={B00000000,B11001110,B11001110,B11001110,B11111110,B11001110,B11001110,B11001110};
static const byte I[]={B00000000,B00111100,B00011000,B00011000,B00011000,B00011000,B00111100,B00111100};
static const byte J[]={B00000000,B01111110,B00001110,B00001110,B00001110,B11001110,B11111110,B01111100};
static const byte K[]={B00000000,B11001110,B11001110,B11011110,B11111100,B11011110,B11001110,B11001110};
static const byte L[]={B00000000,B11000000,B11000000,B11000000,B11000000,B11001110,B11111110,B01111110};
static const byte M[]={B00000000,B11000110,B11101110,B11111110,B11001110,B11001110,B11001110,B11001110};
static const byte N[]={B00000000,B11111100,B11001110,B11001110,B11001110,B11001110,B11001110,B11001110};
static const byte O[]={B00000000,B01111100,B11001110,B11001110,B11001110,B11001110,B11111110,B01111100};
static const byte P[]={B00000000,B11111100,B11001110,B11001110,B11111100,B11000000,B11000000,B11000000};
static const byte Q[]={B00000000,B01111100,B11001110,B11001110,B11011110,B11011110,B11111100,B01110110};
static const byte R[]={B00000000,B11111100,B11001110,B11001110,B11111100,B11001110,B11001110,B11001110};
static const byte S[]={B00000000,B01111000,B11000000,B01111100,B00001110,B11001110,B11111110,B01111100};
static const byte T[]={B00000000,B11111110,B00111000,B00111000,B00111000,B00111000,B01111100,B01111100};
static const byte U[]={B00000000,B11001110,B11001110,B11001110,B11001110,B11001110,B11111110,B01111100};
static const byte V[]={B00000000,B11001110,B11001110,B11001110,B11001110,B11001110,B01111100,B00111000};
static const byte W[]={B00000000,B11001110,B11001110,B11001110,B11001110,B11111110,B11101110,B11000110};
static const byte X[]={B00000000,B11001110,B11001110,B11001110,B01111100,B11001110,B11001110,B11001110};
static const byte Y[]={B00000000,B11001110,B11001110,B01101100,B00111000,B00111000,B01111100,B01111100};
static const byte Z[]={B00000000,B11111100,B00001100,B00011000,B00110000,B01100000,B11111110,B01111110};

// The message.
const byte * figures[] =
{
  hash, F, U, B, A, R
};

// Hacks!
const byte numberOfFigures = sizeof(figures) / sizeof(int);

void setup()
{
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  
  delay(500);
}

void loop()
{
  // Figure out the number of elements and pass everything to 
  drawFigure();
  
  // Wait before repeating.
  delay(1000);
}

// Draws the figures specified in the const byte * figures[].
void drawFigure()
{
  // For each figure...
  for (byte figure = 0; figure < numberOfFigures; figure++)
  {
    const byte * currentFigure = figures[figure];
    
    // To the left, to the left
    for (byte offset = 8; offset > 0; offset--)
    {
      drawRowsOffsetRight(currentFigure, offset);
    }
    
    // Everything you own in the box to the left
    for (byte negativeOffset = 0; negativeOffset <= 8; negativeOffset++)
    {
      drawRowsOffsetLeft(currentFigure, negativeOffset);
    }
  }
}

void drawRowsOffsetRight(const byte figure[], byte offset)
{
  for (byte row = 0; row < ROWS_IN_FIGURE; row++)
  {
    byte toDraw = figure[row] >> offset;
    drawRow(row, toDraw);
  }
  delay(50);
}

void drawRowsOffsetLeft(const byte figure[], byte offset) {
  for (byte row = 0; row < ROWS_IN_FIGURE; row++)
  {
    byte toDraw = figure[row] << offset;
    drawRow(row, toDraw);
  }
  delay(50);
}

void drawRow(byte row, byte toDraw)
{
  lc.setRow(0, row, toDraw);
}

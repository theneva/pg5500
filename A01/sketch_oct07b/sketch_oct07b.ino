#include "LedControl.h"

#define ROWS_IN_FIGURE 8
#define DELAY_TIME_MILLISECONDS 50
#define DELAY_BEFORE_REPEAT_MILLISECONDS 1000

/** (I'm a Java developer)
 * pin 12 is connected to the DataIn
 * pin 11 is connected to the CLK
 * pin 10 is connected to LOAD
 */
LedControl lc = LedControl(12, 11, 10, 1);

static const int space[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
static const int dot[]=  {B00000000,B00000000,B00000000,B00000000,B00000000,B00111100,B00111100,B00111100};
static const int at[]=   {B00111100,B01100110,B01011010,B01010010,B01011010,B01100110,B00111100,B00000000};

static const int A[]={B00000000,B11111100,B11001110,B11001110,B11111110,B11001110,B11001110,B11001110};
static const int B[]={B00000000,B11111100,B11001110,B11111100,B11001110,B11001110,B11111110,B11111100};
static const int C[]={B00000000,B01111100,B11001110,B11000000,B11000000,B11001110,B11111110,B01111100};
static const int D[]={B00000000,B11111100,B11001110,B11001110,B11001110,B11001110,B11111110,B11111100};
static const int E[]={B00000000,B01111100,B11000110,B11110000,B11000000,B11001110,B11111110,B01111100};
static const int F[]={B00000000,B01111110,B11001110,B11000000,B11110000,B11000000,B11000000,B11000000};
static const int G[]={B00000000,B01111100,B11001110,B11000000,B11011110,B11001110,B11111110,B01111100};
static const int H[]={B00000000,B11001110,B11001110,B11001110,B11111110,B11001110,B11001110,B11001110};
static const int I[]={B00000000,B00111100,B00011000,B00011000,B00011000,B00011000,B00111100,B00111100};
static const int J[]={B00000000,B01111110,B00001110,B00001110,B00001110,B11001110,B11111110,B01111100};
static const int K[]={B00000000,B11001110,B11001110,B11011110,B11111100,B11011110,B11001110,B11001110};
static const int L[]={B00000000,B11000000,B11000000,B11000000,B11000000,B11001110,B11111110,B01111110};
static const int M[]={B00000000,B11000110,B11101110,B11111110,B11001110,B11001110,B11001110,B11001110};
static const int N[]={B00000000,B11111100,B11001110,B11001110,B11001110,B11001110,B11001110,B11001110};
static const int O[]={B00000000,B01111100,B11001110,B11001110,B11001110,B11001110,B11111110,B01111100};
static const int P[]={B00000000,B11111100,B11001110,B11001110,B11111100,B11000000,B11000000,B11000000};
static const int Q[]={B00000000,B01111100,B11001110,B11001110,B11011110,B11011110,B11111100,B01110110};
static const int R[]={B00000000,B11111100,B11001110,B11001110,B11111100,B11001110,B11001110,B11001110};
static const int S[]={B00000000,B01111000,B11000000,B01111100,B00001110,B11001110,B11111110,B01111100};
static const int T[]={B00000000,B11111110,B00111000,B00111000,B00111000,B00111000,B01111100,B01111100};
static const int U[]={B00000000,B11001110,B11001110,B11001110,B11001110,B11001110,B11111110,B01111100};
static const int V[]={B00000000,B11001110,B11001110,B11001110,B11001110,B11001110,B01111100,B00111000};
static const int W[]={B00000000,B11001110,B11001110,B11001110,B11001110,B11111110,B11101110,B11000110};
static const int X[]={B00000000,B11001110,B11001110,B11001110,B01111100,B11001110,B11001110,B11001110};
static const int Y[]={B00000000,B11001110,B11001110,B01101100,B00111000,B00111000,B01111100,B01111100};
static const int Z[]={B00000000,B11111100,B00001100,B00011000,B00110000,B01100000,B11111110,B01111110};

// The message.
const int * figures[] =
{
  K, A, R, I, N
};

// Hacks!
const int numberOfFigures = sizeof(figures) / sizeof(int);

void setup()
{
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

void loop()
{
  // Figure out the number of elements and pass everything to 
  drawFigure();
  
  // Wait before repeating.
  delay(DELAY_BEFORE_REPEAT_MILLISECONDS);
}

// Draws the figures specified in the const int * figures[].
void drawFigure()
{
  // For each figure...
  for (int figure = 0; figure < numberOfFigures; figure++)
  {
    const int * currentFigure = figures[figure];
    
    // To the left, to the left
    for (int offset = 8; offset > 0; offset--)
    {
      drawRowsOffsetRight(currentFigure, offset);
      delay(DELAY_TIME_MILLISECONDS);
    }
    
    // Everything you own in the box to the left
    for (int offset = 0; offset <= 8; offset++)
    {
      drawRowsOffsetLeft(currentFigure, offset);
      delay(DELAY_TIME_MILLISECONDS);
    }
  }
}

void drawRowsOffsetRight(const int figure[], int offset)
{
  for (int row = 0; row < ROWS_IN_FIGURE; row++)
  {
    int toDraw = figure[row] >> offset;
    drawRow(row, toDraw);
  }
}

void drawRowsOffsetLeft(const int figure[], int offset) {
  for (int row = 0; row < ROWS_IN_FIGURE; row++)
  {
    int toDraw = figure[row] << offset;
    drawRow(row, toDraw);
  }
}

void drawRow(int row, int toDraw)
{
  lc.setRow(0, row, toDraw);
}

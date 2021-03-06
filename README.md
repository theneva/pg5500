Documentation
=====

**How I figured out how to connect everything**

For reference on the MAX7219, I used [the data sheet available on maximintegrated.com][0].

**Flipping the figures**

I wanted a good overview when connecting the hardware pieces together, and a quick recognition of the LED matrix's pins were crucial to efficient work. Because of this, I decided to connect the matrix rotated 180 degrees around from the way I wanted to display the letters. This meant that all the text would be printed upside down. I identified three ways I could "solve" this "problem":

1. The most obvious fix would be to code the letters rotated 180 degrees.
2. I could have rotated the figures in code before passing them to the MAX7219.
3. I could effectively rotate the characters 180 degrees via hardware through "reversing" the order of *all* of the wires between the MAX7219 and the matrix.

The first option would have made the characters in my code even less readable than it had to be, so I decided against that. The second option didn't seem too efficient, so that's a no there, as well. I went with the third option, as it seemed the least expensive way of achieving what I wanted.

**The LED matrix**

In short, the matrix is controlled by powering entire columns and rows. If you power one row and one column, the one LED where they intersect is lit, and if you power for example one row and two columns, the two LEDs in the intersections will be lit.


**The LedControl library**

I decided to use the [LedControl library][1] for communicating with the MAX7219. The library includes functions like

```c
/* 
 * Set the status of a single Led.
 * Params :
 * addr  address of the display 
 * row   the row of the Led (0..7)
 * col   the column of the Led (0..7)
 * state If true the led is switched on, 
 *	 if false it is switched off
 */
void setLed(int addr, int row, int col, boolean state);
```
    
and (to simplify use), the following.

```c
/* 
  * 1Set all 8 Led's in a row to a new state
  * Params:
  * addr  address of the display
  * row   row which is to be set (0..7)
  * value each bit set to 1 will light up the corresponding Led.
  */
void setRow(int addr, int row, byte value);
```

These switch the requested LEDs on or off, and the only function I've really used for switching LEDs on and off is setRow(...).


**The Fritzing model**

The Fritzing model would work if you connected the 8x8 LED matrix we've been using in the middle with pin 1 in H1. It proved impossible to find a "part" that even resembled the matrix, so I decided to just leave it out of the model.

   [0]: http://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf "MAX7219 data sheet"
   [1]: http://playground.arduino.cc/Main/LedControl "LedControl library on playground.arduino.cc"

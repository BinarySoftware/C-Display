#pragma once

///=============================================================================
///==== Enumeration of all colors possible to print out in Terminal [1] ========
///=============================================================================
typedef enum {
    red,
    boldRed,
    green,
    boldGreen,
    yellow,
    boldYellow,
    blue,
    boldBlue,
    magenta,
    boldMagenta,
    cyan,
    boldCyan,
    defaultColor
} Color;

///=============================================================================
///==== Functions for setting and resetting colors =============================
///=============================================================================
void setColor(Color c);

void resetColor();

Color getRandomColorValue(); /// [2]

/** NOTE [1]
  * There is no difference on my machine between bold and normal colors
  */

/** NOTE [2]
  * Please remember, to "truly randomize", set a seed which will differ from
  * runs, eg. make it dependent of epoch time
  */
#ifndef _COLOR_H
#define _COLOR_H

///=============================================================================
///==== Enumeration of all colors possible to print out in Terminal [1] ========
///=============================================================================
enum Color {
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
};

///=============================================================================
///==== Functions for setting and resetting colors =============================
///=============================================================================
void setColor(enum Color c);

void resetColor();

enum Color getRandomColorValue(); /// [2]

#endif

/** NOTE [1]
  * There is no difference on my machine between bold and normal colors
  */

/** NOTE [2]
  * Please remember, to "truly randomize", set a seed which will differ from
  * runs, eg. make it dependent of epoch time
  */
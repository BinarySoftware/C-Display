#ifndef _COLOR_H
#define _COLOR_H

///=============================================================================
///==== Enumeration of all colors possible to print out in Terminal ============
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

#endif

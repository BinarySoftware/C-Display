#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "color.h"

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

///=============================================================================
///==== Structure for keeping size properties of Terminal ======================
///=============================================================================
struct Size {
    int lines;
    int columns;
};

struct Size getTerminalSize(void);

///=============================================================================
///==== Structure for keeping point char with Color data =======================
///=============================================================================
struct Point {
    char c;
    enum Color color;
};

///=============================================================================
///==== Structure for keeping data of Display ==================================
///=============================================================================
struct Display {
    struct Size size;
    struct Point** array;
};

struct Display initializeDisplay();

///=============================================================================
///==== Display array management and building ==================================
///=============================================================================
struct Point ** initializeArray(int m, int n);

void destroyDisplay(struct Display d);

void makeEmptyDisplay(struct Display d);

void buildDisplay(struct Display d, int isColorMode);

void buildMonochromeDisplay(struct Display d);

void buildColorDisplay(struct Display d);

///=============================================================================
///==== Methods for creating shapes on display =================================
///=============================================================================
void pushCharToPoint(char c, int ln, int col, struct Display d, enum Color color);

void createLine(char c, struct Display d, int ln, int beg, int end, enum Color color);

void createColumn(char c, struct Display d, int col, int beg, int end, enum Color color);

void createDiagonal(char c, struct Display d, int xBeg, int yBeg, int xEnd, int yEnd, enum Color color);

void createLineText(char* c, struct Display d, int ln, int beg, enum Color color);

void createColumnText(char* c, struct Display d, int col, int beg, enum Color color);

void createBox(char c, struct Display d, int xBeg, int yBeg, int xEnd, int yEnd, enum Color color);

void createCircle(char c, struct Display d, int xBeg, int yBeg, int radius, enum Color color);

void createWheel(char c, struct Display d, int xBeg, int yBeg, int radius, enum Color color);

void createSemiWheelDn(char c, struct Display d, int xBeg, int yBeg, int radius, enum Color color);

void createSemiWheelUp(char c, struct Display d, int xBeg, int yBeg, int radius, enum Color color);

void createFrame(char c, struct Display d, enum Color color);


///=============================================================================
///==== DEPRECATED Methods =====================================================
///=============================================================================
__deprecated void createFrameDeprecated(char c, struct Display d, enum Color color);

#endif
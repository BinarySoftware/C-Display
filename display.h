#pragma once

#include "color.h"

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

///=============================================================================
///==== Structure for keeping size properties of Terminal ======================
///=============================================================================
typedef struct {
    int lines;
    int columns;
} Size;

Size getTerminalSize(void);

///=============================================================================
///==== Structure for keeping point char with Color data =======================
///=============================================================================
typedef struct {
    char c;
    Color color;
} Point;

///=============================================================================
///==== Structure for keeping data of Display ==================================
///=============================================================================
typedef struct {
    Size size;
    Point ** array;
} Display;

Display initializeDisplay();

///=============================================================================
///==== Display array management and building ==================================
///=============================================================================
Point ** initializeArray(int m, int n);

void destroyDisplay(Display d);

void makeEmptyDisplay(Display d);

void buildDisplay(Display d, int isColorMode);

void buildMonochromeDisplay(Display d);

void buildColorDisplay(Display d);

///=============================================================================
///==== Methods for creating shapes on display =================================
///=============================================================================
void pushCharToPoint(char c, int ln, int col, Display d, Color color);

void createLine(char c, Display d, int ln, int beg, int end, Color color);

void createColumn(char c, Display d, int col, int beg, int end, Color color);

void createDiagonal(char c, Display d, int xBeg, int yBeg, int xEnd, int yEnd, Color color);

void createLineText(char* c, Display d, int ln, int beg, Color color);

void createColumnText(char* c, Display d, int col, int beg, Color color);

void createBox(char c, Display d, int xBeg, int yBeg, int xEnd, int yEnd, Color color);

void createCircle(char c, Display d, int xBeg, int yBeg, int radius, Color color);

void createWheel(char c, Display d, int xBeg, int yBeg, int radius, Color color);

void createSemiWheelDn(char c, Display d, int xBeg, int yBeg, int radius, Color color);

void createSemiWheelUp(char c, Display d, int xBeg, int yBeg, int radius, Color color);

void createFrame(char c, Display d, Color color);


///=============================================================================
///==== DEPRECATED Methods =====================================================
///=============================================================================
__deprecated void createFrameDeprecated(char c, Display d, Color color);

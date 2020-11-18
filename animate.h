#pragma once

#include "display.h"

///=============================================================================
///==== Animation library for C-Display ========================================
///=============================================================================

void outsideInAnimation(int time, Display d, int isColor, Color color);

void insideOutAnimation(int time, Display d, int isColor, Color color);

int getMaxHalf(Display d);

int getMinHalf(Display d);

#ifndef _ANIMATE_H
#define _ANIMATE_H

#include "display.h"

///=============================================================================
///==== Animation library for C-Display ========================================
///=============================================================================

void outsideInAnimation(int time, struct Display d, int isColor, enum Color color);

void insideOutAnimation(int time, struct Display d, int isColor, enum Color color);

int getMaxHalf(struct Display d);

int getMinHalf(struct Display d);

#endif
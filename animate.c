#include <unistd.h>
#include "animate.h"
///=============================================================================
///==== Outside-In Animation, with specified time per frame ====================
///=============================================================================

void outsideInAnimation(int time, struct Display d, int isColor) {
    createFrame('#', d);
    buildDisplay(d, isColor);
    usleep(time*1000);
    int h = getMinHalf(d);
    for(int i = 0; i <= h; i+=2){
        createBox('#', d, i, i, d.size.columns - i,d.size.lines - i);
        buildDisplay(d, isColor);
        usleep(time*1000);
    }
}

///=============================================================================
///==== Inside-out Animation, with specified time per frame ====================
///=============================================================================

void insideOutAnimation(int time, struct Display d, int isColor) {
    createFrame('#', d);
    buildDisplay(d, isColor);
    usleep(time*1000);
    int halfC = d.size.columns / 2;
    int halfL = d.size.lines / 2;
    int h = getMaxHalf(d);
    for(int i = 0; i <= h; i+=2){
        createBox('#', d, halfC - i, halfL - i, halfC + i ,halfL + i);
        buildDisplay(d, isColor);
        usleep(time*1000);
    }
}

///=============================================================================
///==== Helper functions for getting bigger/smaller half from display size =====
///=============================================================================

int getMaxHalf(struct Display d) {
    int halfC = d.size.columns / 2;
    int halfL = d.size.lines / 2;

    int h;
    if(halfC>halfL){
        h = halfC;
    } else {
        h = halfL;
    }
    return h;
}

int getMinHalf(struct Display d) {
    int halfC = d.size.columns / 2;
    int halfL = d.size.lines / 2;

    int h;
    if(halfC<halfL){
        h = halfC;
    } else {
        h = halfL;
    }
    return h;
}
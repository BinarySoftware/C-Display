#include <stdio.h>
// #include "display.h" - only if not including animate lib
#include "animate.h"

///=============================================================================
///==== Interactive testing environment ========================================
///=============================================================================

int main (void){
    /// First is display initialization - measurement of console, initialization
    /// of properly sized 2D char array to hold data for each point on screen
    struct Display disp = initializeDisplay();

    // Example no.1 - drawing primitive shapes and texts
    printf("Terminal is %d columns by %d lines.\n", disp.size.columns, disp.size.lines);
    createFrame('#', disp);
    createColumn('*', disp, 10, 4, 18);
    createColumn('*', disp, 25, 4, 50);
    createLine('*', disp, 17, 10, 25);
    createColumnText("Co jest ?", disp, 30, 5);
    createLineText("Wszystkiego najlepszego bober!", disp, 52, 15);
    createBox('&',disp,52,40,72,50);
    pushCharToPoint('F', 33, 54, disp);
    buildDisplay(disp);
    getchar();

    // Example no.2 & 3 - animations with C-Display
    makeEmptyDisplay(disp);
    buildDisplay(disp);
    outsideInAnimation(10, disp);
    getchar();

    makeEmptyDisplay(disp);
    buildDisplay(disp);
    insideOutAnimation(10, disp);

    /// Please remember to destroy display before ending app, to free up memory!
    destroyDisplay(disp);
    return 0;
}
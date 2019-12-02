#include <stdio.h>
// #include "display.h" - only if not including animate lib
#include "animate.h"

///=============================================================================
///==== Interactive testing environment ========================================
///=============================================================================

void createGUI(struct Display disp, char c);

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
    pushCharToPoint('F', 33, 54, disp);
    createDiagonal('%',disp,50,8,74,32);
    createDiagonal('%',disp,50,18,74,32);
    createDiagonal('%',disp,50,28,74,32);
    createDiagonal('%',disp,50,38,74,32);
    createDiagonal('%',disp,50,48,74,32);
    createBox('&',disp,52,40,72,50);
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
    getchar();

    // Now it's time for GUI mock-up
    createGUI(disp,'#');
    buildDisplay(disp);
    getchar();

    /// Please remember to destroy display before ending app, to free up memory!
    destroyDisplay(disp);
    return 0;
}

void createGUI(struct Display disp, char c){
    // Cleans up display from previous structures
    makeEmptyDisplay(disp);

    // Creates Empty frame
    createFrame(c, disp);

    // Creates top stucture based on screen width
    int topY = 6;
    createBox(c,disp,0,0,disp.size.columns/3,topY);
    createBox(c,disp,disp.size.columns/3,0,2*disp.size.columns/3,topY);
    createBox(c,disp,2*disp.size.columns/3,0,disp.size.columns,topY);

    createLineText("Foo Bar Baz", disp, 3, 3);
    createLineText("Foo Bar Baz", disp, 3, disp.size.columns/3 + 3);
    createLineText("Foo Bar Baz", disp, 3, 2*disp.size.columns/3 + 3);

    createColumn(c,disp,disp.size.columns/2,topY,disp.size.lines);

    for(int i = 0; i < disp.size.lines-20; i++){
        createLineText("fsafs", disp, i+10, 3);
        createLineText("afisfo af", disp, i+10, disp.size.columns/2 +3);
    }
}
#include <stdio.h>
#include "display.h"

///=============================================================================
///==== Interactive testing environment ========================================
///=============================================================================

int main (void){
    struct Display disp = initializeDisplay();
    printf("Terminal is %d columns by %d lines.\n", disp.size.columns, disp.size.lines);
    createFrame('#', disp);
    createColumn('*', disp, 10, 4, 18);
    createColumn('*', disp, 25, 4, 50);
    createLine('*', disp, 17, 10, 25);
    createColumnText("Co jest ?", disp, 30, 5, 10);
    createLineText("Wszystkiego najlepszego bober!", disp, 52, 15, 50);
    pushCharToPoint('F', 33, 54, disp);
    buildDisplay(disp);
    destroyDisplay(disp);
    return 0;
}
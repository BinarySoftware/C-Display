#include <stdio.h>
// #include "display.h" - only if not including animate lib
#include "animate.h"
#include <limits.h>
#include "life.c"
#include <unistd.h>
#include <stdbool.h>

///=============================================================================
///==== Functions used in this playground ======================================
///=============================================================================

void createGUI(struct Display d, char c);

long fact(long i);

void buildPlayground(struct Display d);

void buildLunaLogo(struct Display d);

void buildAnimations(struct Display d);

void waitForUserInteraction();

void printWorld(golWorld *world, struct Display d);

void runGOL(struct Display d);

///=============================================================================
///==== Interactive testing environment ========================================
///=============================================================================

bool isWaitingForKeyPress = false;

int main (void){
    /// First is display initialization - measurement of console, initialization
    /// of properly sized 2D char array to hold data for each point on screen
    struct Display disp = initializeDisplay();
    disp.size.lines--; // to make sure that "Press Any Key" message will fit

    // Example no.1 - drawing primitive shapes and texts
    buildPlayground(disp);

    // Example no.2 & 3 - animations with C-Display
    buildAnimations(disp);

    // Now it's time for GUI mock-up
    createGUI(disp,'#');

    // And Luna Logo
    buildLunaLogo(disp);

    runGOL(disp);
    /// Please remember to destroy display before ending app, to free up memory!
    destroyDisplay(disp);
    return 0;
}

void buildAnimations(struct Display d){
    makeEmptyDisplay(d);
    buildDisplay(d);
    outsideInAnimation(10, d);
    waitForUserInteraction();

    makeEmptyDisplay(d);
    buildDisplay(d);
    insideOutAnimation(10, d);
    waitForUserInteraction();
}

void buildPlayground(struct Display d){
    printf("Terminal is %d columns by %d lines.\n", d.size.columns, d.size.lines);
    createFrame('#', (d));
    createColumn('*', (d), 10, 4, 18);
    createColumn('*', (d), 25, 4, 50);
    createLine('*', (d), 17, 10, 25);
    createColumnText("Co jest ?", (d), 30, 5);
    createLineText("Wszystkiego najlepszego bober!", (d), 52, 15);
    pushCharToPoint('F', 33, 54, (d));
    createDiagonal('%', (d), 50, 8, 74, 32);
    createDiagonal('%', (d), 50, 18, 74, 32);
    createDiagonal('%', (d), 50, 28, 74, 32);
    createDiagonal('%', (d), 50, 38, 74, 32);
    createDiagonal('%', (d), 50, 48, 74, 32);
    createBox('&', (d), 52, 40, 72, 50);
    createCircle('@',d,d.size.columns/2-1,d.size.lines/2-1,d.size.lines/2-2);
    createWheel('@',d,d.size.columns/2 + 15,d.size.lines/2+15,d.size.lines/5);
    buildDisplay((d));
    waitForUserInteraction();
}

void buildLunaLogo(struct Display d){
    char c = '#';
    makeEmptyDisplay(d);

    int halfY = d.size.lines/2-1;
    int halfX = d.size.columns/2-1;
    for(int i = 2; i <= 4; i++){
        int r = d.size.lines/2-i;
        createCircle(c,d,halfX,halfY,r);
    }
    int semiR = d.size.lines/2-12;
    createSemiWheelDn(c,d,halfX,halfY,semiR);
    int smallWheelR = semiR/2;
    createWheel(' ',d,halfX-smallWheelR,halfY,smallWheelR);
    createWheel(c,d,halfX+smallWheelR,halfY,smallWheelR);
    buildDisplay((d));
    waitForUserInteraction();
}

void createGUI(struct Display d, char c){
    // Cleans up display from previous structures
    makeEmptyDisplay(d);

    // Creates Empty frame
    createFrame(c, d);

    // Creates top structure based on screen width
    int topY = 6;
    createBox(c, d, 0, 0, d.size.columns / 3, topY);
    createBox(c, d, d.size.columns / 3, 0, 2 * d.size.columns / 3, topY);
    createBox(c, d, 2 * d.size.columns / 3, 0, d.size.columns, topY);

    createLineText("Foo Bar Baz", d, 3, 3);
    char text[25];
    sprintf(text, "%ld", LONG_MAX);
    createLineText(text, d, 3, d.size.columns / 3 + 3);
    createLineText("Foo Bar Baz", d, 3, 2 * d.size.columns / 3 + 3);

    createColumn(c, d, d.size.columns / 2, topY, d.size.lines);

    createLineText("Series of Natural numbers", d, topY + 5, 3);
    createLineText("Series of factorials", d, topY + 5, d.size.columns / 2 + 3);

    for(int i = 0; i < 22; i++){
        char t1[5];
        sprintf(t1, "%d", i);
        char t2[25];
        long j = fact(i);
        sprintf(t2, "%ld", j);

        createLineText(t1, d, i + 13, 3);
        createLineText(t2, d, i + 13, d.size.columns / 2 + 3);
    }

    buildDisplay(d);
    waitForUserInteraction();
}

void waitForUserInteraction(){
    if(isWaitingForKeyPress) {
        printf("Press Any Key ...");
    }
    getchar();
}

long fact(long i){
    if(i >= 2){
        long n = i-1;
        return i*fact(n);
    } else {
        return 1;
    }
}

void printWorld(golWorld *world, struct Display d){
    int x, y;

    for(y = 0; y < world->height; y++) {
        for(x = 0; x < world->width; x++) {
            char c = (world->array[y][x]).on ? '#' : ' ';
            pushCharToPoint(c,y,x,d);
        }
    }

    buildDisplay(d);
}

void runGOL(struct Display d) {
    golWorld gameoflife;

    if(createworld(&gameoflife, d.size.columns, d.size.lines)) {
        randomizeworld(&gameoflife);
        int i = 0;
        do {
            printWorld(&gameoflife, d);
            usleep(10*1000);
            updateworld(&gameoflife);
            i++;
        }while(i<1000);

        destroyworld(&gameoflife);
    }
}
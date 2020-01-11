#include <stdio.h>
#include <sys/time.h>
#include <limits.h>
#include <unistd.h>

#include "animate.h"
#include "life.c"
#include "display.h"
#include "color.h"

///=============================================================================
///==== Functions used in this playground ======================================
///=============================================================================

void createGUI(struct Display d, char c, int isColor);

long fact(long i);

void buildPlayground(struct Display d, int isColor);

void buildLunaLogo(struct Display d, int isColor);

void buildAnimations(struct Display d, int isColor);

void waitForUserInteraction(struct Display d, int isColor);

void printWorld(golWorld *world, struct Display d, int isColor);

void runGOL(struct Display d, int isColor);

///=============================================================================
///==== Interactive testing environment ========================================
///============================================================================

long long currentTimeMs() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calc ms
    return milliseconds;
}

int main (void){
    int t = time(0);
    srand(t); // Inicjalizacja losowego ziarna do randomizacji kolorow
    long long timeBeginning = currentTimeMs();

    /// First is display initialization - measurement of console, initialization
    /// of properly sized 2D char array to hold data for each point on screen
    struct Display disp = initializeDisplay();
    /// Prints in color or in monochrome mode
    int isColor = 1;

    // Example no.1 - drawing primitive shapes and texts
    buildPlayground(disp, isColor);

    // Example no.2 & 3 - animations with C-Display
    buildAnimations(disp, isColor);

    // Now it's time for GUI mock-up
    createGUI(disp,'#', isColor);

    // And Luna Logo
    buildLunaLogo(disp, isColor);

    // The last example may be hard for your computer in color mode
    // The Conway's Game of Life
    runGOL(disp, isColor);

    /// Please remember to destroy display before ending app, to free up memory!
    destroyDisplay(disp);

    long long timeEnd = currentTimeMs();
    long long deltaT = timeEnd - timeBeginning;
    printf("Took %lld ms. to render this test bench", deltaT);
    /// Color : 19868ms
    /// Mono  : 18647ms
    /// Color Took 1.065x time to render the same scene, without noticeable FPS drop.
    return 0;
}

void buildAnimations(struct Display d, int isColor){
    makeEmptyDisplay(d);
    buildDisplay(d, isColor);
    outsideInAnimation(10, d, isColor, blue);
    waitForUserInteraction(d, isColor);

    makeEmptyDisplay(d);
    buildDisplay(d, isColor);
    insideOutAnimation(10, d, isColor, yellow);
    waitForUserInteraction(d, isColor);
}

void buildPlayground(struct Display d, int isColor){
    printf("Terminal is %d columns by %d lines.\n", d.size.columns, d.size.lines);
    createFrame('#', (d), getRandomColorValue());
    createColumn('*', (d), 10, 4, 18, getRandomColorValue());
    createColumn('*', (d), 25, 4, 50, getRandomColorValue());
    createLine('*', (d), 17, 10, 25, getRandomColorValue());
    createColumnText("Co jest ?", (d), 30, 5, defaultColor);
    createLineText("Wszystkiego najlepszego bober!", (d), 52, 15, defaultColor);
    pushCharToPoint('F', 33, 54, (d), getRandomColorValue());
    createDiagonal('%', (d), 50, 8, 74, 32, getRandomColorValue());
    createDiagonal('%', (d), 50, 18, 74, 32, getRandomColorValue());
    createDiagonal('%', (d), 50, 28, 74, 32, getRandomColorValue());
    createDiagonal('%', (d), 50, 38, 74, 32, getRandomColorValue());
    createDiagonal('%', (d), 50, 48, 74, 32, getRandomColorValue());
    createBox('&', (d), 52, 40, 72, 50, getRandomColorValue());
    createCircle('@',d,d.size.columns/2-1,d.size.lines/2-1,d.size.lines/2-2, getRandomColorValue());
    createWheel('@',d,d.size.columns/2 + 15,d.size.lines/2+15,d.size.lines/5, getRandomColorValue());
    buildDisplay(d, isColor);
    waitForUserInteraction(d, isColor);
}

void buildLunaLogo(struct Display d, int isColor){
    char c = '#';
    enum Color color = magenta;

    makeEmptyDisplay(d);

    int halfY = d.size.lines/2-1;
    int halfX = d.size.columns/2-1;
    for(int i = 2; i <= 4; i++){
        int r = d.size.lines/2-i;
        createCircle(c,d,halfX,halfY,r, color);
    }
    int semiR = d.size.lines/2-12;
    createSemiWheelDn(c,d,halfX,halfY,semiR, color);
    int smallWheelR = semiR/2;
    createWheel(' ',d,halfX-smallWheelR,halfY,smallWheelR, color);
    createWheel(c,d,halfX+smallWheelR,halfY,smallWheelR, color);
    buildDisplay(d, isColor);
    waitForUserInteraction(d, isColor);
}

void createGUI(struct Display d, char c, int isColor){
    enum Color textColor = blue;
    enum Color frameColor = green;
    // Cleans up display from previous structures
    makeEmptyDisplay(d);

    // Creates Empty frame
    createFrame(c, d, textColor);

    // Creates top structure based on screen width
    int topY = 6;
    createBox(c, d, 0, 0, d.size.columns / 3, topY, textColor);
    createBox(c, d, d.size.columns / 3, 0, 2 * d.size.columns / 3, topY, textColor);
    createBox(c, d, 2 * d.size.columns / 3, 0, d.size.columns, topY, textColor);

    createLineText("Foo Bar Baz", d, 3, 3, frameColor);
    char text[25];
    sprintf(text, "%ld", LONG_MAX);
    createLineText(text, d, 3, d.size.columns / 3 + 3, frameColor);
    createLineText("Foo Bar Baz", d, 3, 2 * d.size.columns / 3 + 3, frameColor);

    createColumn(c, d, d.size.columns / 2, topY, d.size.lines, textColor);

    createLineText("Series of Natural numbers", d, topY + 5, 3, frameColor);
    createLineText("Series of factorials", d, topY + 5, d.size.columns / 2 + 3, frameColor);

    for(int i = 0; i < 22; i++){
        char t1[5];
        sprintf(t1, "%d", i);
        char t2[25];
        long j = fact(i);
        sprintf(t2, "%ld", j);

        createLineText(t1, d, i + 13, 3, frameColor);
        createLineText(t2, d, i + 13, d.size.columns / 2 + 3, frameColor);
    }

    buildDisplay(d, isColor);
    waitForUserInteraction(d, isColor);
}

void waitForUserInteraction(struct Display d, int isColor){
    createLineText(" Press Any Key ... ",d,1,1, defaultColor);
    buildDisplay(d, isColor);;
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

void printWorld(golWorld *world, struct Display d, int isColor) {
    int x, y;

    for (y = 0; y < world->height; y++) {
        for (x = 0; x < world->width; x++) {
            char c = (world->array[y][x]).on ? '#' : ' ';
            pushCharToPoint(c, y, x, d, getRandomColorValue());
        }
    }

    buildDisplay(d, isColor);
}

void runGOL(struct Display d, int isColor) {
    golWorld gameoflife;

    if(createworld(&gameoflife, d.size.columns, d.size.lines)) {
        randomizeworld(&gameoflife);
        int i = 0;
        do {
            printWorld(&gameoflife, d, isColor);
            usleep(10*1000);
            updateworld(&gameoflife);
            i++;
        }while(i<1000);

        destroyworld(&gameoflife);
    }
}
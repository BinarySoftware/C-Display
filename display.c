#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <math.h>

#include "display.h"

///=============================================================================
///==== Creates empty display with specified size ==============================
///=============================================================================
void makeEmptyDisplay(Display d){
    int line = 0;

    while(line < d.size.lines){
        int column = 0;
        while (column < d.size.columns){
            pushCharToPoint(' ', line, column, d, defaultColor);
            column++;
        }
        line++;
    }
}

///=============================================================================
///==== Pushes char to specified point in display's array ======================
///=============================================================================
void pushCharToPoint(char c, int ln, int col, Display d, Color color){
    if(ln < d.size.lines && col < d.size.columns && ln >= 0 && col >= 0){
        d.array[ln][col].c = c;
        d.array[ln][col].color = color;
    }
}

///=============================================================================
///==== Creates lines and columns of specified length ==========================
///=============================================================================
void createLine(char c, Display d, int ln, int beg, int end, Color color){
    for(int i = beg; i < end; i++){
        pushCharToPoint(c, ln, i, d, color);
    }
}

void createColumn(char c, Display d, int col, int beg, int end, Color color){
    for(int i = beg; i < end; i++){
        pushCharToPoint(c, i, col, d, color);
    }
}

///=============================================================================
///==== Creates lines and columns from strings =================================
///=============================================================================
void createLineText(char* c, Display d, int ln, int beg, Color color){
    for(int i = 0; i < d.size.columns-1; i++){
        if(c[i] == '\0'){
            break;
        }
        pushCharToPoint(c[i], ln, i+beg, d, color);
    }
}
void createColumnText(char* c, Display d, int col, int beg, Color color){
    for(int i = 0; i < d.size.lines-1; i++){
        if(c[i] == '\0'){
            break;
        }
        pushCharToPoint(c[i], i+beg, col, d, color);
    }
}

///=============================================================================
///==== Calculates and creates diagonals from start and end points =============
///=============================================================================
void createDiagonal(char c, Display d, int xBeg, int yBeg, int xEnd, int yEnd, Color color){
    float xB = (float) xBeg;
    float yB = (float) yBeg;
    float xE = (float) xEnd;
    float yE = (float) yEnd;

    for(int x = xBeg; x <= xEnd; x++){
        float tga = (yE-yB)/(xE - xB);
        int y = floor(tga*((float)x) + (yE - tga*xE));
        pushCharToPoint(c, y, x, d, color);
    }
}

///=============================================================================
///==== Creates 2D boxes =======================================================
///=============================================================================
void createBox(char c, Display d, int xBeg, int yBeg, int xEnd, int yEnd, Color color){
    if (xBeg == xEnd && yBeg == yEnd) { pushCharToPoint(c, yBeg, xBeg, d, color); }
    else if (xBeg == xEnd) { createColumn(c, d, xBeg, yBeg, yEnd+1, color); }
    else if (yBeg == yEnd) { createLine(c, d, yBeg, xBeg, xEnd, color); }
    else {
        createColumn(c, d, xBeg, yBeg, yEnd, color);
        createColumn(c, d, xEnd, yBeg, yEnd, color);
        createLine(c, d, yBeg, xBeg, xEnd+1, color);
        createLine(c, d, yEnd, xBeg, xEnd+1, color);
    }
}

///=============================================================================
///==== Creates 2D circle ======================================================
///=============================================================================
int reversePythagorean(int x, int r){
    double y = sqrt(pow(r,2)-pow(x,2));
    return ((y)>=0?(int)((y)+0.5):(int)((y)-0.5));
}

void createCircle(char c, Display d, int xBeg, int yBeg, int radius, Color color){
    for(int x = 0; x <= radius; x++){
        int y = reversePythagorean(x,radius);
        pushCharToPoint(c, yBeg + y, xBeg + x, d, color);
        pushCharToPoint(c, yBeg + y, xBeg - x, d, color);
        pushCharToPoint(c, yBeg - y, xBeg + x, d, color);
        pushCharToPoint(c, yBeg - y, xBeg - x, d, color);
    }
}

void createWheel(char c, Display d, int xBeg, int yBeg, int radius, Color color){
    for(int x = 0; x <= radius; x++){
        int y = reversePythagorean(x,radius);
        createColumn(c, d, xBeg + x, yBeg - y, yBeg + y, color);
        createColumn(c, d, xBeg - x, yBeg - y, yBeg + y, color);
    }
}

void createSemiWheelDn(char c, Display d, int xBeg, int yBeg, int radius, Color color){
    for(int x = 0; x <= radius; x++){
        int y = reversePythagorean(x,radius);
        createColumn(c, d, xBeg + x, yBeg , yBeg + y, color);
        createColumn(c, d, xBeg - x, yBeg , yBeg + y, color);
    }
}

void createSemiWheelUp(char c, Display d, int xBeg, int yBeg, int radius, Color color){
    for(int x = 0; x <= radius; x++){
        int y = reversePythagorean(x,radius);
        createColumn(c, d, xBeg + x, yBeg - y, yBeg, color);
        createColumn(c, d, xBeg - x, yBeg - y, yBeg, color);
    }
}

///=============================================================================
///==== Creates a frame ========================================================
///=============================================================================
void createFrameDeprecated(char c, Display d, Color color){
    int line = 0;
    while(line < d.size.lines){
        int column = 0;
        while (column < d.size.columns){
            if (column == 0 || column == d.size.columns - 1 ||
                line == 0 || line == d.size.lines - 1) {
                pushCharToPoint(c, line, column, d,color);
            } else {
                pushCharToPoint(' ', line, column, d, color);
            }
            column++;
        }
        line++;
    }
}

void createFrame(char c, Display d, Color color){
    createBox(c, d, 0, 0, d.size.columns-1, d.size.lines-1, color);
}

///=============================================================================
///==== Builds (prints out) display ============================================
///=============================================================================
void buildDisplay(Display d, int isColorMode){
    if (isColorMode) {
        buildColorDisplay(d);
    } else {
        buildMonochromeDisplay(d);
    }
}

void buildMonochromeDisplay(Display d){
    int line = 0;
    char str[d.size.columns*d.size.lines+1];
    while(line < d.size.lines){
        int column = 0;
        while (column < d.size.columns){
            char c =  d.array[line][column].c;
            // Fix for non-readable ASCII characters
            if (c < 32){
                c = ' ';
            }
            str[d.size.columns*line + column] = c;
            column++;
        }
        line++;
    }
    str[d.size.columns*d.size.lines] = '\0';
    printf("%s", str);
    for (int i = 0; i < d.size.columns*d.size.lines-1; i++) {
        printf("\b");
    }
}

void buildColorDisplay(Display d){
    int line = 0;
    Color previousColor = defaultColor;
    while(line < d.size.lines){
        int column = 0;
        while (column < d.size.columns){
            Point p =  d.array[line][column];
            // Fix for non-readable ASCII characters
            if (p.c < 32){
                p.c = ' ';
            }

            if (previousColor == p.color){
                printf("%c", p.c);
            } else {
                if (p.c != ' ') {
                    setColor(p.color);
                    previousColor = p.color;
                }
                printf("%c", p.c);
            }
            column++;
        }
        line++;
    }
    resetColor();
    for (int i = 0; i < d.size.columns*d.size.lines-1; i++) {
        printf("\b");
    }
}

///=============================================================================
///==== Management of 2D Array & Display =======================================
///=============================================================================
Display initializeDisplay(){
    Size size           = getTerminalSize();
    Point** pointsArray = initializeArray(size.columns, size.lines);
    Display display     = {size, pointsArray};
    makeEmptyDisplay(display);
    return display;
}

Point ** initializeArray(int m, int n){
    Point* values = calloc(m*n, sizeof(Point));
    Point** rows  = malloc(n*sizeof(Point*));
    for (int i=0; i<n; ++i){
        rows[i] = values + i*m;
    }
    return rows;
}

void destroyDisplay(Display d){
    free(*d.array);
    free(d.array);
}

///=============================================================================
///==== Gets the current terminal size properties ==============================
///=============================================================================
Size getTerminalSize(void){
#ifdef TIOCGSIZE
    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    int cols = ts.ts_cols;
    int lines = ts.ts_lines;
    Size r = {lines, cols};
    return r;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
      ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
      int columns = ts.ws_col;
      int lines = ts.ws_row;
      Size r = { columns, lines};
      return r;
#endif
}

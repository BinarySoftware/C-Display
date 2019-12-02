#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <math.h>

#include "display.h"

///=============================================================================
///==== Creates empty display with specified size ==============================
///=============================================================================
void makeEmptyDisplay(struct Display d){
    int line = 0;

    while(line < d.size.lines){
        int column = 0;
        while (column < d.size.columns){
            pushCharToPoint(' ', line, column, d);
            column++;
        }
        line++;
    }
}

///=============================================================================
///==== Pushes char to specified point in display's array ======================
///=============================================================================
void pushCharToPoint(char c, int ln, int col, struct Display d){
    if(ln < d.size.lines && col < d.size.columns && ln >= 0 && col >= 0){
        d.array[ln][col] = c;
    }
}

///=============================================================================
///==== Creates lines and columns of specified length ==========================
///=============================================================================
void createLine(char c, struct Display d, int ln, int beg, int end){
    for(int i = beg; i < end; i++){
        pushCharToPoint(c, ln, i, d);
    }
}

void createColumn(char c, struct Display d, int col, int beg, int end){
    for(int i = beg; i < end; i++){
        pushCharToPoint(c, i, col, d);
    }
}

///=============================================================================
///==== Creates lines and columns from strings =================================
///=============================================================================
void createLineText(char* c, struct Display d, int ln, int beg){
    for(int i = 0; i < d.size.columns-1; i++){
        if(c[i] == '\0'){
            break;
        }
        pushCharToPoint(c[i], ln, i+beg, d);
    }
}
void createColumnText(char* c, struct Display d, int col, int beg){
    for(int i = 0; i < d.size.lines-1; i++){
        if(c[i] == '\0'){
            break;
        }
        pushCharToPoint(c[i], i+beg, col, d);
    }
}

///=============================================================================
///==== Calculates and creates diagonals from start and end points =============
///=============================================================================
void createDiagonal(char c, struct Display d, int xBeg, int yBeg, int xEnd, int yEnd){
    float xB = (float) xBeg;
    float yB = (float) yBeg;
    float xE = (float) xEnd;
    float yE = (float) yEnd;

    for(int x = xBeg; x <= xEnd; x++){
        float tga = (yE-yB)/(xE - xB);
        int y = floor(tga*((float)x) + (yE - tga*xE));
        pushCharToPoint(c,y,x,d);
    }
}

///=============================================================================
///==== Creates 2D boxes =======================================================
///=============================================================================
void createBox(char c, struct Display d, int xBeg, int yBeg, int xEnd, int yEnd){
    if(xBeg == xEnd && yBeg == yEnd){
        pushCharToPoint(c,yBeg,xBeg,d);
    }else if(xBeg == xEnd){
        createColumn(c, d, xBeg,yBeg,yEnd+1);
    }else if(yBeg == yEnd){
        createLine(c, d, yBeg,xBeg,xEnd);
    } else {
        createColumn(c, d, xBeg,yBeg,yEnd);
        createColumn(c, d, xEnd,yBeg,yEnd);
        createLine(c, d, yBeg,xBeg,xEnd+1);
        createLine(c, d, yEnd,xBeg,xEnd+1);
    }
}

///=============================================================================
///==== Creates a frame ========================================================
///=============================================================================
void createFrameDeprecated(char c, struct Display d){
    int line = 0;
    while(line < d.size.lines){
        int column = 0;
        while (column < d.size.columns){
            if (column == 0 || column == d.size.columns - 1){
                pushCharToPoint(c, line, column, d);
            } else if (line == 0 || line == d.size.lines - 1){
                pushCharToPoint(c, line, column, d);
            } else {
                pushCharToPoint(' ', line, column, d);
            }
            column++;
        }
        line++;
    }
}

void createFrame(char c, struct Display d){
    createBox(c,d,0,0,d.size.columns-1,d.size.lines-1);
}

///=============================================================================
///==== Builds (prints out) display ============================================
///=============================================================================
void buildDisplay(struct Display d){
    int line = 0;
    while(line < d.size.lines){
        int column = 0;
        char strLn[d.size.columns];
        while (column < d.size.columns){
            char c =  d.array[line][column];
            // Fix for non-readable ASCII characters
            if (c < 32){
                c = ' ';
            }
            strLn[column] = c;
            column++;
        }
        puts(strLn);
        line++;
    }
}

///=============================================================================
///==== Management of 2D Array & Display =======================================
///=============================================================================
struct Display initializeDisplay(){
    struct Size size = getTerminalSize();
    char** array = initializeArray(size.columns, size.lines);
    struct Display display = {size, array};
    makeEmptyDisplay(display);
    return display;
}

char** initializeArray(int m, int n){
    char* values = calloc(m*n, sizeof(char));
    char** rows = malloc(n*sizeof(char*));
    for (int i=0; i<n; ++i){
        rows[i] = values + i*m;
    }
    return rows;
}

void destroyDisplay(struct Display d){
    free(*d.array);
    free(d.array);
}

///=============================================================================
///==== Gets the current terminal size properties ==============================
///=============================================================================
struct Size getTerminalSize(void){
#ifdef TIOCGSIZE
    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    int cols = ts.ts_cols;
    int lines = ts.ts_lines;
    struct Size r = {lines, cols};
    return r;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
      ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
      int columns = ts.ws_col;
      int lines = ts.ws_row;
      struct Size r = { columns, lines};
      return r;
#endif
}

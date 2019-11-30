#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>

#include "display.h"

///=============================================================================
///==== Creates empty display with specified size ==============================
///=============================================================================
void makeEmptyDisplay(struct Display d){
    int line = 0;

    while(line < d.size.lines){
        int column = 0;
        while (column < d.size.columns){
            d.array[line][column] = ' ';
            column++;
        }
        line++;
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
                d.array[line][column] = c;
            } else if (line == 0 || line == d.size.lines - 1){
                d.array[line][column] = c;
            } else {
                d.array[line][column] = ' ';
            }
            column++;
        }
        line++;
    }
}

void createFrame(char c, struct Display d){
    createColumn(c, d, 0,0,d.size.lines);
    createColumn(c, d, d.size.columns-1,0,d.size.lines);
    createLine(c, d, 0,0,d.size.columns);
    createLine(c, d, d.size.lines-1,0,d.size.columns);
}

void createLine(char c, struct Display d, int ln, int beg, int end){
    for(int i = beg; i < end; i++){
        d.array[ln][i] = c;
    }
}

void createColumn(char c, struct Display d, int col, int beg, int end){
    for(int i = beg; i < end; i++){
        d.array[i][col] = c;
    }
}

void createLineText(char* c, struct Display d, int ln, int beg, int len){
    for(int i = 0; i < len-1; i++){
        if (i+beg < d.size.columns) {
            d.array[ln][i+beg] = c[i];
        }
    }
}
void createColumnText(char* c, struct Display d, int col, int beg, int len){
    for(int i = 0; i < len-1; i++){
        if (i+beg < d.size.lines) {
            d.array[i+beg][col] = c[i];
        }
    }
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

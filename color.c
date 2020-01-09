#include <stdio.h>

#include "color.h"

void setColor(enum Color c){
    char escape[] = "\033";
    char * col;
    switch (c) {
        case red:
            col = "[0;31m";
            break;
        case boldRed:
            col = "[1;31m";
            break;
        case green:
            col = "[0;32m";
            break;
        case boldGreen:
            col = "[1;32m";
            break;
        case yellow:
            col = "[0;33m";
            break;
        case boldYellow:
            col = "[1;33m";
            break;
        case blue:
            col = "[0;34m";
            break;
        case boldBlue:
            col = "[1;34m";
            break;
        case magenta:
            col = "[0;35m";
            break;
        case boldMagenta:
            col = "[1;35m";
            break;
        case cyan:
            col = "[0;36m";
            break;
        case boldCyan:
            col = "[1;36m";
            break;
        default:
            col = "[0m";
            break;
    }
    printf("%s%s",escape,col);
    printf("\b");
}

void resetColor(){
    char escape[] = "\033";
    char col[] = "[0m";
    printf("%s%s",escape,col);
    printf("\b");
}
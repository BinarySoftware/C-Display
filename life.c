//
// Created by Uranium-239
// http://www.rohitab.com/discuss/topic/33623-conways-game-of-life-in-cc/
//
// Modified by BinarySoftware
//

#include <stdlib.h>

typedef struct golCell {
    struct golCell *neighbours[8];
    int on;
} golCell;

typedef struct golWorld {
    golCell **array;
    int width;
    int height;
    void *mem;
} golWorld;

void randomizeworld(golWorld *world){
    int x, y;

    for(y = 0; y < world->height; y++) {
        for(x = 0; x < world->width; x++) {
            (world->array[y][x]).on = rand() & 1;
        }
    }
}

void updateworld(golWorld *world){
    int x, y, i, neighbours;

    for(y = 0; y < world->height; y++) {
        for(x = 0; x < world->width; x++, neighbours = 0) {
            for(i = 0; i < 8; i++) {
                if ((world->array[y][x].neighbours[i]) &&
                    ((world->array[y][x]).neighbours[i]->on & 1)) {
                    neighbours++;
                }
            }
            if((neighbours < 2) || (neighbours > 3)){
                (world->array[y][x]).on |= 2;
            } else if(neighbours == 3){
                (world->array[y][x]).on |= 4;
            }
        }
    }

    for(y = 0; y < world->height; y++) {
        for(x = 0; x < world->width; x++) {
            if(world->array[y][x].on & 4){
                world->array[y][x].on = 1;
            } else if (world->array[y][x].on & 2){
                world->array[y][x].on = 0;
            }
        }
    }
}

void destroyworld(golWorld *world){
    free(world->mem);
}

int createworld(golWorld *world, int width, int height){
    int i, j;
    unsigned long base   = sizeof(golCell *) * height;
    unsigned long rowlen = sizeof(golCell) * width;

    if(!(world->mem = calloc(base + (rowlen * height), 1))) {
        return 0;
    }

    world->array  = world->mem;
    world->width  = width;
    world->height = height;

    for(i = 0; i < height; i++) {
        world->array[i] = world->mem + base + (i * rowlen);
    }

    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            if(j != 0) {
                (world->array[i][j]).neighbours[3] = &(world->array[i][j - 1]);
            }

            if(i != 0) {
                (world->array[i][j]).neighbours[1] = &(world->array[i - 1][j]);
            }

            if(j != (width - 1)) {
                (world->array[i][j]).neighbours[4] = &(world->array[i][j + 1]);
            }

            if(i != (height - 1)) {
                (world->array[i][j]).neighbours[6] = &(world->array[i + 1][j]);
            }

            if((i != 0) && (j != 0)) {
                (world->array[i][j]).neighbours[0] = &(world->array[i - 1][j - 1]);
            }

            if((i != (height - 1)) && (j != (width - 1))) {
                (world->array[i][j]).neighbours[7] = &(world->array[i + 1][j + 1]);
            }

            if((i != (height - 1)) && (j != 0)) {
                (world->array[i][j]).neighbours[5] = &(world->array[i + 1][j - 1]);
            }

            if((i != 0) && (j != (width - 1))) {
                (world->array[i][j]).neighbours[2] = &(world->array[i - 1][j + 1]);
            }
        }
    }

    return 1;
}
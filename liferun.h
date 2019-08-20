#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //sleep func
#include <ctype.h>
#include <string.h>
#include <signal.h>

#define SET_BIT_ON(value, bit_position) ((value) |= 1UL << (bit_position))
#define SET_BIT_OFF(value, bit_position) ((value) |= 0 << (bit_position))

#define BOARD_HEIGHT 40 //24
#define BOARD_WIDTH 140 //80

char *verbose[30];

int end = 0;

int randomvalue;
FILE *fpointer;

int bits = 64;
unsigned int maxSeed;

unsigned short state[BOARD_HEIGHT][BOARD_WIDTH]; //1st [] defines rows, 2nd [] defines length for each row (column)

int draw_init(int size_rows, int size_cols);

int draw_life(int rows, int cols, short *state);

void draw_finish();
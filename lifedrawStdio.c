#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //sleep func

#define update() printf("\033[H\033[J")          //Clear the screen
#define gotoxy(x, y) printf("\033[%d;%dH", x, y) //navigate in the screen according to coordinates x,y

/*
* returns -1 if it can not initialize
*/
int draw_init(int size_rows, int size_cols)
{
    printf("\033[H");
    time_t t;
    srand(time(NULL)); //init random seed
}

/*
* returns negative number if the drawing failed for some reason
*/
int draw_life(int rows, int cols, short *state)
{
    int index = 0;
    gotoxy(0, 0);
    int i, j;
    for (i = 0; i < rows; i++)
    {
        //usleep(100);
        for (j = 0; j < cols; j++)
        {
            index = (i * cols) + j;
            if (state[index] & (1 << 14))
                printf("X");
            else
                printf(" ");
            //usleep(100);
        }
        printf("\n");
    }
    fflush(stdout);

    return 0;
}

/*
* always successful
*/
void draw_finish()
{
    //leave me here
}
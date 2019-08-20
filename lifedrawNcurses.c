#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR)
    {
        ungetch(ch);
        endwin();
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
* returns -1 if it can not initialize
*/
int draw_init(int size_rows, int size_cols)
{
    initscr(); 
    cbreak();
    nodelay(stdscr, TRUE);                            //initialize curses
    curs_set(0);                           //hide cursor
    noecho();                              //don't display any key inputs
    start_color();                         //background color start
    COLOR_PAIR(1);                         //define color in index 1
    init_pair(1, COLOR_BLUE, COLOR_BLACK); //set the forebackgound and background color for index 1
    attron(COLOR_PAIR(1));
}

/*
* returns negative number if the drawing failed for some reason
*/
int draw_life(int rows, int cols, short *state)
{
    int index = 0;
    int i, j;
    for (i = 0; i < rows; i++)
    {
        usleep(500);
        for (j = 0; j < cols; j++)
        {
            COLOR_PAIR(i);
            init_pair(i, random(), COLOR_BLACK);
            attron(COLOR_PAIR(i));

            move(i, j);
            index = (i * cols) + j;
            if (state[index] & (1 << 14))
                addch(ACS_DIAMOND); //addch(ACS_CKBOARD); //printw("#");
            else
                printw(" ");
            //usleep(100);
        }
    }
    refresh();

    if (kbhit())
        return 1;

    return 0;
}

/*
* always successful
*/
void draw_finish()
{
}
#include "liferun.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int is_given_bit_set(unsigned value, int bitPosition)
{
    int result = value >> bitPosition;
    return result & 1; //& bitwise comparing 1st bit position
}

//Dead: 0 or Alive: 1
int isAlive(unsigned short cell)
{
    unsigned short p = cell;
    int isAlive = is_given_bit_set(p, 14);

    return isAlive;
}

/* Discover who are my neighbors*/
int get_neighbors(int row, int col)
{
    int count_neighbors = 0;

    int top = row - 1;
    int bott = row + 1;
    int left = col - 1;
    int right = col + 1;

    int x, y, total = 0;
    for (y = row - 1; y <= row + 1; y++)
    {
        if (y < 0 || y > BOARD_HEIGHT)
            continue;

        for (x = col - 1; x <= col + 1; x++)
        {
            if (x < 0 || x > BOARD_WIDTH)
                continue;

            if (!(y == row && x == col))
                count_neighbors += isAlive(state[y][x]);
        }
    }

    return count_neighbors;
}

/* 
* see_which_rule_apply 

    **** Living cells
        < 2 nb dies
        > 3 nb dies
        2 or 3 lives

    **** Dead cells
        == 3 if it's a dead cell then lives

*/
int keep_cell_alive(int h, int w)
{
    _Bool isCellAlive = isAlive(state[h][w]);
    _Bool keep_alive = 0;

    int neighbor_cells_alive = get_neighbors(h, w);
    if (isCellAlive)
        keep_alive = (neighbor_cells_alive == 2 || neighbor_cells_alive == 3);
    else
        keep_alive = (neighbor_cells_alive == 3);
}

//print unsigned variables in binary
void bin(unsigned n)
{
    unsigned i;
    printf("[");
    for (i = 1 << 15; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
    printf("] ");
}

//randomly return 1 or 0
int generate_random_bit(int uRandom)
{
    if (uRandom)
    {
        if (fpointer == NULL)
            fpointer = fopen("/dev/urandom", "rb");

        fread(&randomvalue, sizeof(int), 1, fpointer);

        return (randomvalue % 2);
    }
    else
    {
        maxSeed = (1 << (bits - 1)) - 1;
        return is_given_bit_set((rand() % maxSeed), 30); //return bit in 29 bit position
    }
}

void calculate_next_generation()
{
    int h, w;
    for (h = 0; h < BOARD_HEIGHT; h++)
    {
        for (w = 0; w < BOARD_WIDTH; w++)
        {
            _Bool keep_alive = keep_cell_alive(h, w);

            if (keep_alive)
                state[h][w] = SET_BIT_ON(state[h][w], 15);
            else
                state[h][w] = SET_BIT_OFF(state[h][w], 15);
        }
    }
}


int set_state_from_file(unsigned short *state, char *p)
{
    char *pch, *pch2;
    char buffer[100];
    FILE *f;
    f = fopen(p, "r"); //reads the file

    if (f == NULL)
        return 0;

    int idx = 0;
    while (fgets(buffer, 100, f))
    {
        pch = strtok(buffer, " ");
        pch2 = strtok(NULL, " ");

        if (pch == NULL || pch2 == NULL)
            return -1;

        idx = atoi(pch) * BOARD_WIDTH + atoi(pch2);
        state[idx] = 1 << 14;
    }
    return 1;
}

void init_board(unsigned short *state) //initialize the board wit random seed
{
    int i, j, random_bit;

    int uRandom = 0;
    if (*verbose == NULL || (uRandom = strncmp(*verbose, "--random", 8) == 0) || !set_state_from_file(state, *verbose))
    {
        for (i = 0; i < BOARD_HEIGHT; i++)
        {
            for (j = 0; j < BOARD_WIDTH; j++)
            {
                /* 3 init random seed */
                random_bit = generate_random_bit(uRandom);

                state[i * BOARD_WIDTH + j] = random_bit << 14;
            }
        }

        if (fpointer != NULL)
            fclose(fpointer);
    }
}

int shift_next_generation()
{
    int i, j;
    unsigned short value;
    for (i = 0; i < BOARD_HEIGHT; i++)
        for (j = 0; j < BOARD_WIDTH; j++)
        {
            state[i][j] = state[i][j] >> 1;
        }
}

void intHandler(int dummy) {
    end = 1;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, intHandler);

    if (argc > 1)
        *verbose = argv[1];

    draw_init(BOARD_HEIGHT, BOARD_WIDTH);

    init_board(*state);

    while (1)
    {
        calculate_next_generation();
        end = draw_life(BOARD_HEIGHT, BOARD_WIDTH, *state);
        shift_next_generation();

        if (end)
            return 0;
    }

    return 0;
}
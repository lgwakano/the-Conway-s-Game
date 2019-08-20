# the-Conway-s-Game
An infinite two-dimensional orthogonal grid of square cell


The universe of the Game is an infinite two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, alive or dead. 

Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur: 

1. Any live cell with fewer than two live neighbours dies, as if caused by under-population. 
2. Any live cell with two or three live neighbours lives on to the next generation. 
3. Any live cell with more than three live neighbours dies, as if by over-population. 
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.


## Compiling the program
1. Using curses Curses
  `gcc liferun.c lifedrawNcurses.c -lcurses -o name_of_compiled_file`
 
2. Using Stdio
  `gcc liferun.c lifedrawStdio.c -o name_of_compiled_file`

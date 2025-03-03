#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define WALL_CHAR '#'
#define FLOOR_CHAR ' '

#define M2G(x) (2*x+1) // Map to Grid coordinate conversion

typedef enum {
  N,
  E,
  S,
  W,
  DIR_SIZE
} Direction;

typedef struct grid {
  int w, h;
  char *data;
} Grid;

typedef struct cell_location{
  int x;
  int y;
} Cell;

void initGrid(Grid *g, int w, int h, int walled);
void freeGrid(Grid *g);
void printGrid(Grid *g);
void printBlockGrid(Grid *g);
bool digToward(Grid *g, Cell c, Direction d);
bool fillToward(Grid *g, Cell c, Direction d);
bool isCellVisited(Grid *g, Cell c);
bool isCellValid(Grid *g, Cell c);
Cell goDir(Cell c, Direction d);

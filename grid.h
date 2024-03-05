#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define WALL_CHAR '#'
#define SPACE_CHAR ' '

typedef struct grid {
  int w, h;
  char *data;
} Grid;

typedef struct cell_location{
  int x;
  int y;
} Cell;

Grid *newGrid(int w, int h);
void printGrid(Grid *g);
void printBlockGrid(Grid *g);
void setCell(Grid *g, Cell c,  char s);
char getCell(Grid *g, int x, int y);
bool isEdge(Grid *g, Cell c);
bool isValidCell(Grid *g, int x, int y);

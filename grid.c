#include "grid.h"
#include <string.h>
#include <stdio.h>

void initGrid(Grid *g, int w, int h, int walled) {
  unsigned board_size = M2G(w)*M2G(h);
  g->w = w;
  g->h = h;
  g->data = (char *)malloc(board_size);
  if (g->data == NULL) {
    fprintf(stderr, "Error initializing the grid");
    return;
  }
  if (walled) { // Cells are walled off
    memset(g->data, WALL_CHAR, board_size);
    for (unsigned i = 0; i < h; i++)
      for (unsigned j = 0; j < w; j++)
        g->data[M2G(i) * M2G(w) + M2G(j)] = FLOOR_CHAR;
  } 
  else {
    memset(g->data, FLOOR_CHAR, board_size);
    // put walls around as the boundary
    memset(g->data, WALL_CHAR, M2G(w));
    memset(g->data + M2G(h-1)*M2G(w), WALL_CHAR, M2G(w));
    for (unsigned i = 1; i < M2G(h) - 1; i++) {
      g->data[i * M2G(w)] = WALL_CHAR;
      g->data[(i + 1) * M2G(w) - 1] = WALL_CHAR;
    }
  }
}

void freeGrid(Grid *g) {
  free(g->data);
}

// Helper funcs to work with grid squares
// Square of Grid != Cell of Map
static char getSquare(Grid *g, int x, int y) {
  return g->data[x*M2G(g->w) + y];
}

static void setSquare(Grid *g, int x, int y, char s) {
  g->data[x*M2G(g->w) + y] = s;
}

static bool isBorderSquare(Grid *g, int x, int y) {
  return (x <= 0
        || x >= M2G(g->w) - 1
        || y <= 0
        || y >= M2G(g->h) - 1);
}
// -------------------------- //

void printGrid(Grid *g) {
  for(int i = 0; i < M2G(g->h); i++) {
    for (int j = 0; j < M2G(g->w); j++) {
      printf("%c", g->data[i*M2G(g->w) + j]);
    }
    printf("\n");
  }
}

void printBlockGrid(Grid *g) {
  for(int i = 0; i < M2G(g->h); i++) {
    for (int j = 0; j < M2G(g->w); j++) {
      if (g->data[i*M2G(g->w) + j] == FLOOR_CHAR) {
	      printf("  ");
      } else {
      	printf("\x1b[7m");
	      printf("  ");
	      printf("\x1b[0m");
      }
    }
    printf("\n");
  }
}

bool setToward(Grid *g, Cell c, Direction d, char s) {
  unsigned tx = M2G(c.x);
  unsigned ty = M2G(c.y);
  switch(d) {
  case N:
    ty -= 1;
    break;
  case S:
    ty += 1;
    break;
  case E:
    tx += 1;
    break;
  case W:
    tx -= 1;
    break;
  default:
    fprintf(stderr, "DIR_SIZE is used in setToward");
    break;
  }
  if (isBorderSquare(g, tx, ty))
    return false;
  setSquare(g, tx, ty, s);
  return true;
}

bool digToward(Grid *g, Cell c, Direction d) {
  return setToward(g, c, d, FLOOR_CHAR);
}

bool fillToward(Grid *g, Cell c, Direction d) {
  return setToward(g, c, d, WALL_CHAR);
}

static unsigned getCellConnectionCount(Grid *g, Cell c) {
  unsigned x = M2G(c.x);
  unsigned y = M2G(c.y);
  unsigned count = 0;
  if (getSquare(g, x, y-1) == FLOOR_CHAR) count++;
  if (getSquare(g, x+1, y) == FLOOR_CHAR) count++;
  if (getSquare(g, x, y+1) == FLOOR_CHAR) count++;
  if (getSquare(g, x-1, y) == FLOOR_CHAR) count++;
  return count;
}

bool isCellVisited(Grid *g, Cell c) {
  return getCellConnectionCount(g, c) > 0;
}

bool isCellValid(Grid *g, Cell c) {
  return (c.x >= 0
        && c.x < g->w
        && c.y >= 0
        && c.y < g->h);
}

Cell goDir(Cell c, Direction d) {
  if (d == N) return (Cell){ c.x, c.y-1 };
  if (d == S) return (Cell){ c.x, c.y+1 };
  if (d == E) return (Cell){ c.x+1, c.y };
  if (d == W) return (Cell){ c.x-1, c.y };
  else {
    fprintf(stderr, "DIR_SIZE is used in goDir");
    return c;
  }
}

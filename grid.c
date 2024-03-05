#include "grid.h"

Grid *newGrid(int w, int h) {
  Grid *temp = malloc(sizeof(Grid));
  temp->w = w;
  temp->h = h;
  temp->data = (char *)malloc(w*h);
  memset(temp->data, WALL_CHAR, w*h);
  return temp;
}

void printGrid(Grid *g) {
  for(int i = 0; i < g->h; i++) {
    for (int j = 0; j < g->w; j++) {
      printf("%c", g->data[i*g->w + j]);
    }
    printf("\n");
  }
}

void printBlockGrid(Grid *g) {
  for(int i = 0; i < g->h; i++) {
    for (int j = 0; j < g->w; j++) {
      if (g->data[i*g->w + j] == SPACE_CHAR) {
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

void setCell(Grid *g, Cell c, char s) {
  g->data[c.x*g->w + c.y] = s;
}

char getCell(Grid *g, int x, int y) {
  return g->data[x*g->w + y];
}

bool isEdge(Grid *g, Cell c) {
  return c.x <= 0 || c.x >= g->w -1 || c.y <= 0 || c.y >= g->h -1;
}

static int getCellNeighborCount(Grid *g, int x, int y) {
  int count = 0;
  if (!isEdge(g, (Cell){x, y-1}) && getCell(g, x, y-1) == SPACE_CHAR) count++;
  if (!isEdge(g, (Cell){x+1, y}) && getCell(g, x+1, y) == SPACE_CHAR) count++;
  if (!isEdge(g, (Cell){x, y+1}) && getCell(g, x, y+1) == SPACE_CHAR) count++;
  if (!isEdge(g, (Cell){x-1, y}) && getCell(g, x-1, y) == SPACE_CHAR) count++;
  return count;
}

bool isValidCell(Grid *g, int x, int y) {
  return !isEdge(g, (Cell){x, y}) && getCellNeighborCount(g, x, y) <= 1;
}

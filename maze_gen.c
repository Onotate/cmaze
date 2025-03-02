#include "maze_gen.h"

Cell carveTorward(Grid *g, Cell c, Direction d) {
  Cell target;
  switch (d) {
  case N:
    target = (Cell) {c.x, c.y-2};
    setCell(g, (Cell) {c.x, c.y-1}, SPACE_CHAR);
    break; 
  case E:
    target = (Cell) {c.x+2, c.y};
    setCell(g, (Cell) {c.x+1, c.y}, SPACE_CHAR);
    break;
  case S:
    target = (Cell) {c.x, c.y+2};
    setCell(g, (Cell) {c.x, c.y+1}, SPACE_CHAR);
    break;
  case W:
    target = (Cell) {c.x-2, c.y};
    setCell(g, (Cell) {c.x-1, c.y}, SPACE_CHAR);
    break;
  }
  setCell(g, target, SPACE_CHAR);
  return target;
}

Grid *gtree(Grid *g, Cell start, int (*sampler)(int)) {
  Pool current;
  initPool(&current, g->w*g->h);
  Direction ndata[4];
  int ncount = 0;

  setTimedSeed();

  // Attempt to visit the starting cell
  if (isEdge(g, start)) {
    return NULL;
  } else {
    setCell(g, start, SPACE_CHAR);
    addCellIntoPool(&current, start);
  }

  // Growing loop
  while (current.size != 0) {
    int sel_index = (*sampler)(current.size);
    Cell sel_cell = getCellFromPool(&current, sel_index);

    // Get possible valid neighbors
    ncount = 0;
    if (getCell(g, sel_cell.x, sel_cell.y-2) == WALL_CHAR && isValidCell(g, sel_cell.x, sel_cell.y-2)) {  // n
      ndata[ncount] = N;
      ncount++;
    }
    if (getCell(g, sel_cell.x, sel_cell.y+2) == WALL_CHAR && isValidCell(g, sel_cell.x, sel_cell.y+2)) {  // s
      ndata[ncount] = S;
      ncount++;
    }
    if (getCell(g, sel_cell.x-2, sel_cell.y) == WALL_CHAR && isValidCell(g, sel_cell.x-2, sel_cell.y)) {  // w
      ndata[ncount] = W;
      ncount++;
    }
    if (getCell(g, sel_cell.x+2, sel_cell.y) == WALL_CHAR && isValidCell(g, sel_cell.x+2, sel_cell.y)) {  // e
      ndata[ncount] = E;
      ncount++;
    }

    // Choose a random neighbor to carve toward or pop selected from pool
    if (ncount > 0) {
      Direction dir = ndata[random_sampler(ncount)];
      Cell nchosen = carveTorward(g, sel_cell, dir);
      addCellIntoPool(&current, nchosen);
    } else {
      delCellFromPool(&current, sel_index);
    }
  }

  freePool(&current);
  return g;
}

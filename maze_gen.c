#include "maze_gen.h"

Grid *gtree(Grid *g, Cell start, int (*cell_sampler)(int)) {
  Pool *current = newPool(g->w*g->h);
  Cell ndata[4];
  int ncount = 0;

  setTimedSeed();

  // Attempt to visit the starting cell
  if (isEdge(g, start)) {
    return NULL;
  } else {
    setCell(g, start, SPACE_CHAR);
    addCellIntoPool(current, start);
  }

  // Growing loop
  while (current->size != 0) {
    int sel_index = (*cell_sampler)(current->size);
    Cell sel_cell = getCellFromPool(current, sel_index);

    // Get possible valid neighbors
    ncount = 0;
    if (getCell(g, sel_cell.x, sel_cell.y-1) == WALL_CHAR && isValidCell(g, sel_cell.x, sel_cell.y-1)) {  // n
      ndata[ncount] = (Cell){sel_cell.x, sel_cell.y - 1};
      ncount++;
    }
    if (getCell(g, sel_cell.x, sel_cell.y+1) == WALL_CHAR && isValidCell(g, sel_cell.x, sel_cell.y+1)) {  // s
      ndata[ncount] = (Cell){sel_cell.x, sel_cell.y + 1};
      ncount++;
    }
    if (getCell(g, sel_cell.x-1, sel_cell.y) == WALL_CHAR && isValidCell(g, sel_cell.x-1, sel_cell.y)) {  // w
      ndata[ncount] = (Cell){sel_cell.x - 1, sel_cell.y};
      ncount++;
    }
    if (getCell(g, sel_cell.x+1, sel_cell.y) == WALL_CHAR && isValidCell(g, sel_cell.x+1, sel_cell.y)) {  // e
      ndata[ncount] = (Cell){sel_cell.x + 1, sel_cell.y};
      ncount++;
    }

    // Choose a random neighbor to carve toward or pop selected from pool
    if (ncount > 0) {
      Cell nchosen = ndata[random_sampler(ncount)];
      setCell(g, nchosen, SPACE_CHAR);
      addCellIntoPool(current, nchosen);
    } else {
      delCellFromPool(current, sel_index);
    }
  }

  freePool(current);
  return g;
}

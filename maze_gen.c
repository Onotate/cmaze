#include "maze_gen.h"

void digMaze(Grid *g, Cell start, int (*sampler)(int)) {
  Pool current;
  initPool(&current, g->w*g->h);
  Direction ndata[4];
  int ncount = 0;

  setTimedSeed();

  addCellIntoPool(&current, start);

  // Growing loop
  while (current.size != 0) {
    int sel_index = (*sampler)(current.size);
    Cell sel_cell = getCellFromPool(&current, sel_index);

    // Get possible valid direction to dig to
    ncount = 0; 
    for (Direction d = 0; d < DIR_SIZE; d++) {
      Cell candidate = goDir(sel_cell, d);
      if (isCellValid(g, candidate) && !isCellVisited(g, candidate)) {
        ndata[ncount] = d;
        ncount++;
      }
    }

    // Choose a random direction to dig toward or pop selected from pool
    if (ncount > 0) {
      Direction dir = ndata[random_sampler(ncount)];
      digToward(g, sel_cell, dir);
      Cell nchosen = goDir(sel_cell, dir);
      addCellIntoPool(&current, nchosen);
    } else {
      delCellFromPool(&current, sel_index);
    }
  }

  freePool(&current);
}

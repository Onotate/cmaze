#include "maze_gen.h"

#define W 25
#define H 25
#define START_X 3   // < W
#define START_Y 3   // < H

int main() {
  Grid g;
  initGrid(&g, W, H, 1);
  Cell start = (Cell){START_X, START_Y};
  digMaze(&g, start, &rdfs_sampler); // can be switched out for random_sampler
  printBlockGrid(&g);
  freeGrid(&g);
  return 0;
}

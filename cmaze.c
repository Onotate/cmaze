#include "maze_gen.h"

#define W 25
#define H 25
#define START_X 3
#define START_Y 3

int main() {
  Grid *g = newGrid(2*W+1, 2*H+1);
  Cell start = (Cell){2*START_X+1, 2*START_Y+1};
  g = gtree(g, start, &rdfs_sampler); // can be switched out for random_sampler
  printBlockGrid(g);
  return 0;
}

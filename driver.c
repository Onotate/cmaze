#include "maze_gen.h"

int main() {
  Grid *g = newGrid(50, 50);
  Cell start = (Cell){6, 7};
  g = gtree(g, start, &random_sampler);
  printBlockGrid(g);
  return 0;
}

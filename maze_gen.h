#include "pool.h"
#include "sampler.h"

typedef enum {
  N,
  E,
  S,
  W
} Direction;

Grid *gtree(Grid *g, Cell start, int (*cell_sampler)(int));

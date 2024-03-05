#include "pool.h"
#include "sampler.h"

Grid *gtree(Grid *g, Cell start, int (*cell_sampler)(int));

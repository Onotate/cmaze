#include "sampler.h"

void setTimedSeed() {
  /* Set random seed using srand() and time().
   */
  srand((unsigned int)time(NULL));
  return;
}

int rdfs_sampler(int size) {
  return size-1;
}

int random_sampler(int size) {
  int div = RAND_MAX/size;
  int r;
  while ( (r = rand() / div) > size - 1);
  return r;
}

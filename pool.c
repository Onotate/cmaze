#include "pool.h"

void initPool(Pool *pool, int max_size) {
  pool->data = malloc(max_size * sizeof(Cell));
  pool->size = 0;
}

void freePool(Pool *p) {
  free(p->data);
  return;
}

Cell getCellFromPool(Pool *p, int index){
  return p->data[index];
}

void delCellFromPool(Pool *p, int index) {
  for (int i = index + 1; i < p->size; i++) {
    p->data[i-1] = p->data[i];
  }
  p->size = p->size - 1;
  return;
}

void addCellIntoPool(Pool *p, Cell c) {
  p->data[p->size] = c;
  p->size = p->size + 1;
  return;
}

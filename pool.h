#include "grid.h"

typedef struct cell_pool {
  Cell *data;
  int size;
} Pool;

Pool *newPool(int max_size);
void freePool(Pool *p);
Cell getCellFromPool(Pool *p, int index);
void delCellFromPool(Pool *p, int index);
void addCellIntoPool(Pool *p, Cell c);

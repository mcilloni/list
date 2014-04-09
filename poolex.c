#include "pool.h"

#include <stdlib.h>

int main(void) {

  Pool *pool = pool_new();

  for (size_t i = 0; i < 100; ++i) {
    pool_alloc(pool, 100U);
  }

  pool_release(pool, free);

}

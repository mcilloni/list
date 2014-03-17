#include "list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

  List *list = list_new();

  list_appendint(list, 33);
  printf("list[%lu] == %lu, len == %zu\n", 0LU, *list_getint(list, 0), list_len(list));


  list_appendint(list, 0);
  printf("list[%lu] == %lu, len == %zu\n", 1LU, *list_getint(list, 1), list_len(list));

  list_appendint(list, 12);
  printf("list[%lu] == %lu, len == %zu\n", 2LU, *list_getint(list, 2), list_len(list));

  list_prune(list);

  for (uint8_t i = 0; i < 31; ++i) {
    list_appendint(list, i);
  }

  bool inside = false;
  fputs("[ ", stdout);
  for (uint8_t i = 0; i < 31; ++i) {
    if (inside) {
      fputs(", ",stdout);
    } else {
      inside = true;
    }

    printf("%lu", *list_getint(list, i));
  }
  puts(" ]");

  list_free(list);
  return EXIT_SUCCESS;
}


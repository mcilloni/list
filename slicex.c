#include "list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printlist(List *list) {
  bool inside = false;
  fputs("[ ", stdout);
  size_t len = list_len(list);
  for (uint8_t i = 0; i < len; ++i) {
    if (inside) {
      fputs(", ",stdout);
    } else {
      inside = true;
    }

    printf("%lu", *list_getint(list, i));
  }
  puts(" ]");
}

int main(void) {

  srand(time(NULL));

  List *list = list_new();

  for (uint8_t i = 0; i < 31; ++i) {
    list_appendint(list, i);
  }

  printlist(list);

  List *slice = list_slice(list, 3, 11);

  printlist(slice);

  list_free(slice);

  slice = list_slice(list, 12, -1);

  printlist(slice);

  list_free(slice);

  slice = list_slice(list, 12, 100);

  printlist(slice);

  list_free(slice);

  list_free(list);
  return EXIT_SUCCESS;
}


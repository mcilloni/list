#include "list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

  List *list = list_new();

  const char *lol = "lol", *folz = "folz";

  list_append(list, lol);
  list_append(list, folz);

  bool inside = false;
  size_t len = list_len(list);
  fputs("[ ", stdout);
  for (uint8_t i = 0; i < len; ++i) {
    if (inside) {
      fputs(", ",stdout);
    } else {
      inside = true;
    }

    printf("%s", (char*) *list_get(list, i));
  }
  puts(" ]");

  list_free(list);
  return EXIT_SUCCESS;
}

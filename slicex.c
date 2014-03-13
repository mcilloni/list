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

  List *list = list_new();

  for (uint8_t i = 0; i < 31; ++i) {
    list_appendint(list, i);
  }

  fputs("list[] == ", stdout);

  printlist(list);

  List *extract = list_extract(list, 3, 11);

  fputs("list[3:14] == ", stdout);
  printlist(extract);

  fputs("list[] == ", stdout);
  printlist(list);

  list_free(extract);

  extract = list_extract(list, 12, -1);

  fputs("list[12:] == ", stdout);
  printlist(extract);

  list_free(extract);
 
  fputs("list[] == ", stdout); 
  printlist(list);

  puts("list[3] = 23");

  list_addint(list, 3, 23);

  fputs("list[] == ", stdout);
  printlist(list);

  list_free(list);
  return EXIT_SUCCESS;
}


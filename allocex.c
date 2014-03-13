#include "list.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>



int main(void) {

  List *arr = list_new();

  for (uint8_t i = 0; i < 31; ++i) {
    list_append(arr, malloc(sizeof(char)));
  }

  list_freeAll(arr, free);

  return EXIT_SUCCESS;
}


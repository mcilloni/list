#include "list.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct node {
  struct node *prec,*succ;
  uintptr_t value;
};

struct list {
  struct node *start, *end;
  size_t len;

  struct node *current;
  size_t pos;  

  bool isSlice;
};

int64_t (*list_append)(List *list, const void *val) = (int64_t (*)(List*,const void*)) list_appendint;

int64_t list_appendint(List *list, uintptr_t val) {

  if (list->isSlice) {
    return -1;
  }

  if (!list->start) {
    list_pushint(list, val);
    return 1;
  }
  
  struct node *new = calloc(1, sizeof(struct node));

  new->value = val;

  new->prec = list->end;
  list->end->succ = new;
  
  list->end = new;
  
  return (list->len)++;
}

void node_free(struct node *node) {
  if (node) {
    node_free(node->succ);
    free(node);
  }
}

void list_free(List *list) {
  if (!list->isSlice) {
    node_free(list->start);
  }

  free(list);
}

void node_freeAll(struct node *node, void (*freefunc)(void*)) {

  if (node) {
    node_freeAll(node->succ, freefunc);
    freefunc((void*) node->value);
    free(node);
  }
}

void list_freeAll(List *list, void (*freefunc)(void*)) {
  if (!list->isSlice) {
    node_freeAll(list->start, freefunc);
  }

  free(list);
}

void node_freeContents(struct node *node, void (*freefunc)(void*)) {
  if (node) {
    node_freeContents(node->succ, freefunc);
    freefunc((void*) node->value);
  }
}

void list_freeContents(List *list, void (*freefunc)(void*)) {
  if (!list->isSlice) {
    node_freeContents(list->start, freefunc);
  }
}

void** (*list_get)(List *list, size_t pos) = (void** (*) (List*,size_t)) list_getint;

void list_seekAhead(List *list, size_t pos) {
  
  if (!list->current) {
    list->current = list->start;
    list->pos = 0LU;
  }

  for (; list->pos < pos; ++list->pos) {
    list->current = list->current->succ;
  }

}

void list_seekBehind(List *list, size_t pos) {

  if(!list->current) {
    list->current = list->end;
    list->pos = list->len - 1;
  }

  for (; list->pos > pos; --list->pos) {
    list->current = list->current->prec;
  }

}

void list_seek(List *list, size_t pos) {
  switch ((pos > list->pos) - (pos < list->pos)) {
  case 1:
    list_seekAhead(list, pos);
  case -1:
    list_seekBehind(list, pos);
  default:
    break;
  }
}

uintptr_t* list_getint(List *list, size_t pos) {

  if (pos >= list->len) {
    return NULL;
  }

  list_seek(list, pos);

  return (list->current) ? &list->current->value : NULL;
}

int64_t (*list_insert)(List *list, size_t pos, const void *val) = (int64_t (*)(List*,size_t,const void*)) list_insertint;

int64_t list_insertint(List *list, size_t pos, uintptr_t val) {
  
  if (pos > list->len) {
    return -1;
  }  

  if (pos == list->len) {
    return list_appendint(list, val);  
  }

  list_seek(list, pos);

  list->current->value = val;

  return list->pos;
}

size_t list_len(List *list) {
  return list->len;
}

List* list_new(void) {
  return calloc(1, sizeof(List));
}


void* (*list_pop)(List *list) = (void* (*)(List*)) list_popint;

uintptr_t list_popint(List *list) {
  if (!list->start) {
    return 0;
  }

  if (list->isSlice) {
    return 0;
  }

  struct node *next = list->start->succ;
  uintptr_t ret = list->start->value;

  free(list->start);

  next->prec = NULL;
  
  if (list->start == list->end) {
    memset(list, 0, sizeof *list);
  } else {
    list->start = next;
  }

  return ret;
}

void list_prune(List *list) {
  if (!list->isSlice) {
    node_free(list->start);
    memset(list, 0, sizeof *list);
  }
}


void (*list_push)(List *list, const void *val) = (void (*)(List*,const void*)) list_pushint;

void list_pushint(List *list, uintptr_t val) {

  if (list->isSlice) {
    return;
  }

  struct node *new = calloc(1, sizeof(struct node));

  new->succ = list->start;
  if (list->start) {
    list->start->prec = new;  
  }

  if (!list->end) {
    list->end = new;
    list->current = new;
  } else {
    ++list->pos;
  }

  new->value = val;
  list->start = new;

  ++list->len;
}

List* list_shallowCopy(List *list) {
  List *new = list_new();
  size_t len = list_len(list);
  for (size_t i = 0; i < len; ++i) {
    list_appendint(new, *list_getint(list, i));
  }

  return new;
}                                     
                                                 
List* list_slice(List *list, size_t start, int64_t len) {

  List *slice = list_new();
  slice->isSlice = true;

  if (start < list->len) {
    len = (len > list->len) ? (list->len - start) : len;
    len = (len >= 0) ? len : (list->len - start);
    list_seek(list, start);
    slice->current = slice->start = slice->end = list->current;
    if (len > 1) {
      list_seek(list, start + len - 1);
      slice->end = list->current;
    }

    slice->len = len;
  }

  return slice;

}

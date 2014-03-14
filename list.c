#include "list.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct lnode {
  struct lnode *prec,*succ;
  uintptr_t value;
};

struct list {
  struct lnode *start, *end;
  size_t len;

  struct lnode *current;
  size_t pos;  
};

void list_seek(List*,size_t);

int64_t (*list_add)(List *list, size_t pos, const void *val) = (int64_t (*)(List*,size_t,const void*)) list_addint;

int64_t list_addint(List *list, size_t pos, uintptr_t val) {
  if (pos > list->len) {
    return -1;
  }

  if (pos == list->len) {
    return list_appendint(list, val);
  }

  list_seek(list, pos);

  struct lnode *new = calloc(1, sizeof(struct lnode));
  struct lnode *prec = list->current->prec;

  if (prec) {
    prec->succ = new;
  }

  new->prec = prec;
  new->value = val;
  new->succ = list->current;
  list->current->prec = new;

  list->current = (void*) (list->pos = 0);

  ++list->len;

  return pos;
}

int64_t (*list_append)(List *list, const void *val) = (int64_t (*)(List*,const void*)) list_appendint;

int64_t list_appendint(List *list, uintptr_t val) {

  if (!list->start) {
    list_pushint(list, val);
    return 1;
  }
  
  struct lnode *new = calloc(1, sizeof(struct lnode));

  new->value = val;

  new->prec = list->end;
  list->end->succ = new;
  
  list->end = new;
  
  return (list->len)++;
}

List* list_extract(List *list, size_t start, int64_t len) {

  List *extract = list_new();

  if (start < list->len) {
    len = (len > list->len) ? (list->len - start) : len;
    len = (len >= 0) ? len : (list->len - start);
    list_seek(list, start);

    struct lnode *prec = list->current->prec;
    struct lnode **link1;
    if (prec) {
      link1 = &prec->succ;
    } else {
      link1 = &list->start;
    }

    extract->current = extract->start = extract->end = list->current;

    list_seek(list, start + len - 1);

    struct lnode *succ = list->current->succ;
    struct lnode **link2;
    if (succ) {
      link2 = &succ->prec;
    } else {
      link2 = &list->end;
    }

    extract->end = list->current;

    extract->len = len;

    *link1 = succ;
    *link2 = prec;

    extract->start->prec = extract->end->succ = NULL;

    list->len -= len;

    list->current = list->start;
    list->pos = 0LU;
  }

  return extract;

}

void lnode_free(struct lnode *lnode) {
  if (lnode) {
    lnode_free(lnode->succ);
    free(lnode);
  }
}

void list_free(List *list) {
  lnode_free(list->start);

  free(list);
}

void lnode_freeAll(struct lnode *lnode, void (*freefunc)(void*)) {

  if (lnode) {
    lnode_freeAll(lnode->succ, freefunc);
    freefunc((void*) lnode->value);
    free(lnode);
  }
}

void list_freeAll(List *list, void (*freefunc)(void*)) {
  lnode_freeAll(list->start, freefunc);

  free(list);
}

void lnode_freeContents(struct lnode *lnode, void (*freefunc)(void*)) {
  if (lnode) {
    lnode_freeContents(lnode->succ, freefunc);
    freefunc((void*) lnode->value);
  }
}

void list_freeContents(List *list, void (*freefunc)(void*)) {
  lnode_freeContents(list->start, freefunc);
}

void** (*list_get)(List *list, size_t pos) = (void** (*) (List*,size_t)) list_getint;

void list_seekAhead(List *list, size_t pos) {
  
  if (!list->current || !pos) {
    list->current = list->start;
    list->pos = 0LU;
  }

  for (; list->pos < pos; ++list->pos) {
    list->current = list->current->succ;
  }

}

void list_seekBehind(List *list, size_t pos) {

  if(!list->current || ((list->len - 1) == pos)) {
    list->current = list->end;
    list->pos = list->len - 1;
  }

  for (; list->pos > pos; --list->pos) {
    list->current = list->current->prec;
  }

}

void list_seek(List *list, size_t pos) {
  if (!list->current && !pos) {
    list->current = list->start;
    list->pos = 0;
  }

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

  struct lnode *next = list->start->succ;
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
  lnode_free(list->start);
  memset(list, 0, sizeof *list);
}


void (*list_push)(List *list, const void *val) = (void (*)(List*,const void*)) list_pushint;

void list_pushint(List *list, uintptr_t val) {

  struct lnode *new = calloc(1, sizeof(struct lnode));

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
                                                 

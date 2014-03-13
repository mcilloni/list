#if !defined(_LIST_H)
#define _LIST_H

#include <stddef.h>
#include <stdint.h>

typedef struct list List;

extern int64_t (*list_add)(List *list, size_t pos, const void *val);
int64_t list_addint(List *list, size_t pos, uintptr_t val);
extern int64_t (*list_append)(List *list, const void *val);
int64_t list_appendint(List *list, uintptr_t val);
List* list_extract(List *list, size_t start, int64_t len);
void list_free(List *list);
void list_freeAll(List *list, void (*freefunc)(void*));
void list_freeContents(List *list, void (*freefunc)(void*));
extern void** (*list_get)(List *list, size_t pos);
uintptr_t* list_getint(List *list, size_t pos);
extern int64_t (*list_insert)(List *list, size_t pos, const void *val);
int64_t list_insertint(List *list, size_t pos, uintptr_t val);
size_t list_len(List *list);
List* list_new(void);
extern void* (*list_pop)(List *list);
uintptr_t list_popint(List *list);
void list_prune(List *list);
extern void (*list_push)(List *list, const void *val);
void list_pushint(List *list, uintptr_t val);
List* list_shallowCopy(List* list);

#endif

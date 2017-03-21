
#ifndef MALLOC_270_H
#define MALLOC_270_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void*  dlmalloc(size_t);
void   dlfree(void*);
void*  dlcalloc(size_t, size_t);
void*  dlrealloc(void*, size_t);

#ifdef __cplusplus
};  /* end of extern "C" */
#endif

#endif /* MALLOC_270_H */

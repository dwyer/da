#ifndef __DA_H__
#define __DA_H__

#include <stddef.h>

#ifndef DA_STDINT
#define DA_STDINT 1
#endif

#define da_cap(da) ((da)->cap)
#define da_len(da) ((da)->len)
#define da_maxlen(da) (INT_MAX / (da)->spec->size)
#define da_ismutable(da) ((da)->cap >= 0)

typedef void da_init_func_t(void *);
typedef void da_copy_func_t(void *, const void *);
typedef void da_free_func_t(void *);
typedef int da_cmp_func_t(const void *, const void *);

typedef struct {
    size_t size;
    da_init_func_t *init;
    da_copy_func_t *copy;
    da_free_func_t *free;
} da_spec_t;

typedef struct {
    const da_spec_t *spec;
    void *data;
    int len;
    int cap;
} da_t;

extern da_t *da_new(const da_spec_t *sp);
extern void da_init(da_t *da, const da_spec_t *sp);
extern void da_deinit(da_t *da);
extern void da_free(da_t *da);

extern da_t *da_copy(da_t *dst, const da_t *src);

extern void *da_get(const da_t *da, int i);
extern void da_set(da_t *da, int i, const void *ep);
extern void da_setcap(da_t *da, int cap);
extern void da_append(da_t *da, const void *ep);
extern void da_extend(da_t *da1, const da_t *da2);
extern void *da_pop(da_t *da);
extern void da_clear(da_t *da);

extern void _da_assert(int expr, const char *msg, ...);

extern da_t da_slice_val(const da_t *src, int i, int j);
extern da_t *da_slice(da_t *dst, const da_t *src, int i, int j);
extern void da_sort(da_t *da, int (*cmp)(const void *, const void *));

/* for setting custom allocators */
extern void *(*da_realloc)(void *, size_t);
extern void (*da_dealloc)(void *);

extern int da_default_cap;

#endif

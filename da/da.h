#ifndef __DA_H__
#define __DA_H__

#include <stddef.h>

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

/**
 * Allocates and initializes a new da with the given spec and returns it. The
 * returned value must be freed to avoid memory leaks.
 */
extern da_t *da_new(const da_spec_t *sp);

/**
 * Initialize a previously allocated da with the given spec.
 */
extern void da_init(da_t *da, const da_spec_t *sp);

/**
 * Deinitializes the given da. If `da`'s `spec`'s `free` pointer is set,
 * it is called on all the members. `da`'s internal memory is then cleared.
 */
extern void da_deinit(da_t *da);

/**
 * Deinitializes the given da then deallocates it.
 */
extern void da_free(da_t *da);

/**
 * Creates a copy of `src` and its elements to `dst` and returns `dst`. If `dst`
 * if `NULL`, it will be allocated.
 */
extern da_t *da_copy(da_t *dst, const da_t *src);

/**
 * Returns a pointer to the element at the given index `i`. If `i` if negative,
 * it will return a element relative to the end of the array.
 */
extern void *da_get(const da_t *da, int i);

/**
 * Sets the element at the given index `i`. If `i` is negative it will set the
 * element relative to the end of the array.
 */
extern void da_set(da_t *da, int i, const void *ep);

/**
 * Sets the capacity of `da` to AT MOST the given `cap` and allocates enough
 * internal memory to support that capacity. If the internal capacity is higher
 * than `cap`, nothing happens.
 */
extern void da_setcap(da_t *da, int cap);

/**
 * Pushes the given element to the end of `da`.
 */
extern void da_append(da_t *da, const void *ep);

/**
 * Pushes the elements of `src` to the end of `dst`.
 */
extern void da_extend(da_t *dst, const da_t *src);

/**
 * Pops and returns the last element of `da`.
 */
extern void *da_pop(da_t *da);

/**
 * Clears the elements of `da`, but doesn't free its internal memory.
 */
extern void da_clear(da_t *da);

extern void _da_assert(int expr, const char *msg, ...);

extern da_t da_slice_val(const da_t *src, int i, int j);

/**
 * Sets the elements of `dst` to the elements of `src` in the range between
 * `i` and `j`, then returns `dst`.
 *
 * `dst` is assumed to be uninitialized. If `dst` is `NULL`, it will be
 * allocated.
 *
 * NOTE: `dst` will contain the same internal memory of as `src`. The elements
 * will not be copied. Mutating the elements of one will mutate the elements of
 * the other. `dst` itself cannot be appended to or extended.
 */
extern da_t *da_slice(da_t *dst, const da_t *src, int i, int j);

/**
 * Sorts in place the elements of the array with the given `cmp` function.
 */
extern void da_sort(da_t *da, int (*cmp)(const void *, const void *));

/**
 * A pointer to the internal `realloc` function. This can be overridden with a
 * custom allocator.
 *
 * Default is `realloc`.
 */
extern void *(*da_realloc)(void *, size_t);

/**
 * A pointer to the internal `free` function. The can be overridden with a
 * custom deallocator.
 *
 * Default is `free`.
 */
extern void (*da_dealloc)(void *);

/**
 * The internal default capacity. This can be overridden. The default is 1.
 */
extern int da_default_cap;

#endif

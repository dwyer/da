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


#define _DA_DECL_NEW(suf, T) \
    da_t *da_new_##suf(void)


#define _DA_DEF_NEW(suf, T) \
    _DA_DECL_NEW(suf, T) { \
        da_t *da = da_new(&da_spec_##suf); \
        return da; \
    }


#define _DA_DECL_INIT(suf, T) \
    void da_init_##suf(da_t *da)


#define _DA_DEF_INIT(suf, T) \
    _DA_DECL_INIT(suf, T) { \
        da_init(da, &da_spec_##suf); \
    }


#define _DA_DECL_GET(suf, T) \
    T da_get_##suf(const da_t *da, int i)


#define _DA_DEF_GET(suf, T) \
    _DA_DECL_GET(suf, T) { \
        _da_assert(da->spec == &da_spec_##suf, \
                "da_get_" # suf ": da_t passed does not support type " # T); \
        return *(T *)da_get(da, i); \
    }


#define _DA_DECL_SET(suf, T) \
    void da_set_##suf(da_t *da, int i, T e)


#define _DA_DEF_SET(suf, T) \
    _DA_DECL_SET(suf, T) { \
        _da_assert(da->spec == &da_spec_##suf, \
                "da_set_" # suf ": da_t passed does not support type " # T); \
        da_set(da, i, &e); \
    }


#define _DA_DECL_POP(suf, T) \
    T da_pop_##suf(da_t *da)


#define _DA_DEF_POP(suf, T) \
    _DA_DECL_POP(suf, T) { \
        _da_assert(da->spec == &da_spec_##suf, \
                "da_pop_" # suf ": da_t passed does not support type " # T); \
        return *(T *)da_pop(da); \
    }


#define _DA_DECL_APPEND(suf, T) \
    void da_append_##suf(da_t *da, T e)


#define _DA_DEF_APPEND(suf, T) \
    _DA_DECL_APPEND(suf, T) { \
        _da_assert(da->spec == &da_spec_##suf, \
                "da_append_" # suf ": da_t passed does not support type " # T); \
        da_append(da, &e); \
    }


#define DA_DECL_SPEC(suf, T) \
    da_spec_t da_spec_##suf


#define DA_DEF_SPEC(suf, T, init, copy, free) \
    DA_DECL_SPEC(suf, T) = {sizeof(T), init, copy, free}


#define DA_DECL_HELPERS(suf, T) \
    extern const DA_DECL_SPEC(suf, T); \
    extern _DA_DECL_NEW(suf, T); \
    extern _DA_DECL_INIT(suf, T); \
    extern _DA_DECL_GET(suf, T); \
    extern _DA_DECL_SET(suf, T); \
    extern _DA_DECL_POP(suf, T); \
    extern _DA_DECL_APPEND(suf, T);


#define DA_DEF_HELPERS_EX(suf, T, init, copy, free) \
    const DA_DEF_SPEC(suf, T, init, copy, free); \
    extern _DA_DEF_NEW(suf, T); \
    extern _DA_DEF_INIT(suf, T); \
    extern _DA_DEF_GET(suf, T); \
    extern _DA_DEF_SET(suf, T); \
    extern _DA_DEF_POP(suf, T); \
    extern _DA_DEF_APPEND(suf, T);


#define DA_DEF_HELPERS(suf, T) \
    DA_DEF_HELPERS_EX(suf, T, NULL, NULL, NULL);


DA_DECL_HELPERS(c, char);
DA_DECL_HELPERS(d, double);
DA_DECL_HELPERS(f, float);
DA_DECL_HELPERS(i, int);
DA_DECL_HELPERS(l, long);
DA_DECL_HELPERS(ll, long long);
DA_DECL_HELPERS(s, char *);
DA_DECL_HELPERS(uc, unsigned char);
DA_DECL_HELPERS(ui, unsigned int);
DA_DECL_HELPERS(ul, unsigned long);
DA_DECL_HELPERS(ull, unsigned long long);


#if DA_STDINT
#include <stdint.h>
DA_DECL_HELPERS(i8, int8_t);
DA_DECL_HELPERS(i16, int16_t);
DA_DECL_HELPERS(i32, int32_t);
DA_DECL_HELPERS(i64, int64_t);
DA_DECL_HELPERS(u8, uint8_t);
DA_DECL_HELPERS(u16, uint16_t);
DA_DECL_HELPERS(u32, uint32_t);
DA_DECL_HELPERS(u64, uint64_t);
#endif

#endif

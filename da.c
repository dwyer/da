#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "da/da.h"
#include "da/da_util.h"

#ifndef DA_DEFAULT_CAP
#define DA_DEFAULT_CAP 1
#endif

typedef unsigned char u8;

void *(*da_realloc)(void *, size_t) = realloc;
void (*da_dealloc)(void *) = free;

int da_default_cap = DA_DEFAULT_CAP;


extern void da_init(da_t *da, const da_spec_t *sp)
{
    da->spec = sp;
    da->data = NULL;
    da->len = 0;
    da->cap = 0;
}


extern da_t *da_new(const da_spec_t *sp)
{
    da_t *da = da_realloc(NULL, sizeof(*da));
    da_init(da, sp);
    return da;
}


extern void da_deinit(da_t *da)
{
    if (da->data) {
        if (da_ismutable(da)) {
            da_clear(da);
            da_dealloc(da->data);
        }
        da->data = NULL;
    }
    da->cap = 0;
}


extern void da_free(da_t *da)
{
    da_deinit(da);
    da_dealloc(da);
}


extern da_t *da_copy(da_t *dst, const da_t *src)
{
    int i;
    if (dst)
        da_init(dst, src->spec);
    else
        dst = da_new(src->spec);
    for (i = 0; i < da_len(src); ++i)
        da_append(dst, da_get(src, i));
    return dst;
}


extern void *da_get(const da_t *da, int i)
{
    if (i < 0)
        i += da->len;
    _da_assert(i >= 0 && i < da->len, "da_get: index %d out of bounds for 0..<%d",
            i, da->len);
    return (u8 *)da->data + (da->spec->size * i);
}


extern void da_set(da_t *da, int i, const void *ep)
{
    if (i < 0)
        i += da->len;
    _da_assert(i >= 0 && i < da->len, "da_set: index out of bounds");
    if (da->spec->copy)
        da->spec->copy((u8 *)da->data + da->spec->size * i, ep);
    else
        memcpy((u8 *)da->data + da->spec->size * i, ep, da->spec->size);
}


extern void da_setcap(da_t *da, int cap)
{
    _da_assert(da_ismutable(da), "da_setcap: passed immutable array\n");
    if (da->cap >= cap)
        return;
    da->cap = cap;
    da->data = da_realloc(da->data, da->cap * da->spec->size);
}


static void da_setlen(da_t *da, int n)
{
    _da_assert(da_ismutable(da), "da_setlen: passed immutable array\n");
    _da_assert(n >= 0, "da_setlen: passed negative length\n");
    da->len = n;
    if (da->cap < da->len) {
        int cap = da->cap ? da->cap : da_default_cap;
        while (cap < da->len) {
            if (cap < 1024)
                cap *= 2;
            else
                cap += cap / 4;
        }
        da_setcap(da, cap);
    }
}


extern void da_append(da_t *da, const void *ep)
{
    _da_assert(da_ismutable(da), "da_append: passed immutable array\n");
    da_setlen(da, da->len+1);
    da_set(da, da->len-1, ep);
}


extern void da_extend(da_t *dst, const da_t *src)
{
    int i;
    _da_assert(da_ismutable(dst), "da_extend: passed immutable array\n");
    _da_assert(dst->spec == src->spec,
            "da_extend: dst and src spec mismatch\n");
    i = dst->len;
    da_setlen(dst, dst->len + src->len);
    memcpy((u8 *)dst->data + dst->spec->size * i, src->data, dst->spec->size * src->len);
}


extern void *da_pop(da_t *da)
{
    void *e;
    _da_assert(da_len(da) > 0, "da_pop: passed zero-length array\n");
    e = da_get(da, -1);
    da->len--;
    return e;
}


extern void da_clear(da_t *da)
{
    int i;
    if (da->spec->free)
        for (i = 0; i < da_len(da); ++i)
            da->spec->free(da_get(da, i));
    da->len = 0;
}


extern da_t *da_slice(da_t *dst, const da_t *src, int i, int j)
{
    _da_assert(i <= j, "da_slice: invalid range: i must be less than or equal to j\n");
    _da_assert(i <= src->len, "da_slice: i must be [0..da_len(da)]\n");
    _da_assert(j <= src->len, "da_slice: j must be [0..da_len(da)]\n");
    if (dst == NULL)
        dst = da_realloc(NULL, sizeof(*dst));
    dst->spec = src->spec;
    dst->data = (u8 *)src->data + src->spec->size * i;
    dst->len = j - i;
    dst->cap = -1;
    return dst;
}


extern da_t da_slice_val(const da_t *src, int i, int j)
{
    da_t da;
    return *da_slice(&da, src, i, j);
}


extern void da_sort(da_t *da, int (*cmp)(const void *, const void *))
{
    qsort(da->data, da->len, da->spec->size, cmp);
}


extern void _da_assert(int expr, const char *msg, ...)
{
    if (!expr) {
        va_list args;
        va_start(args, msg);
        vfprintf(stderr, msg, args);
        fputc('\n', stderr);
        va_end(args);
        exit(1);
    }
}


static void _copy_s(char **dst, const char **src)
{
    *dst = *src ? strdup(*src) : NULL;
}


static void _free_s(char **sp)
{
    da_dealloc(*sp);
}


DA_DEF_HELPERS(c, char)
DA_DEF_HELPERS(d, double)
DA_DEF_HELPERS(f, float)
DA_DEF_HELPERS(i, int)
DA_DEF_HELPERS(l, long)
DA_DEF_HELPERS_EX(s, char *, NULL, (da_copy_func_t *)_copy_s,
        (da_free_func_t *)_free_s)
DA_DEF_HELPERS(uc, unsigned char)
DA_DEF_HELPERS(ui, unsigned int)
DA_DEF_HELPERS(ul, unsigned long)

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

DA_DEF_HELPERS(ll, long long)
DA_DEF_HELPERS(ull, unsigned long long)

#include <stdint.h>

DA_DEF_HELPERS(i8, int8_t)
DA_DEF_HELPERS(i16, int16_t)
DA_DEF_HELPERS(i32, int32_t)
DA_DEF_HELPERS(i64, int64_t)
DA_DEF_HELPERS(u8, uint8_t)
DA_DEF_HELPERS(u16, uint16_t)
DA_DEF_HELPERS(u32, uint32_t)
DA_DEF_HELPERS(u64, uint64_t)

#endif

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> // rand
#include <string.h>

#include "da.h"

#define NUM_ITERS 1000000
#define DEFAULT_CAP 1


static size_t da_num_allocs = 0;
static size_t da_bytes_alloced = 0;


static void *_realloc(void *dst, size_t size)
{
    da_num_allocs++;
    da_bytes_alloced += size;
    return realloc(dst, size);
}


void test_floats(void)
{
    da_t *sins = da_new_f();
    da_setcap(sins, NUM_ITERS);
    for (int i = 0; i < NUM_ITERS; ++i)
        da_append_f(sins, sinf(i));
    for (int i = 0; i < NUM_ITERS; ++i)
        assert(da_get_f(sins, i) == sinf(i));
    da_free(sins);
    fprintf(stderr, "test_floats passed\n");
}


void test_doubles(void)
{
    da_t *roots = da_new_d();
    da_setcap(roots, NUM_ITERS);
    for (int i = 0; i < NUM_ITERS; ++i)
        da_append_d(roots, sqrt(i));
    for (int i = 0; i < NUM_ITERS; ++i)
        assert(da_get_d(roots, i) == sqrt(i));
    da_free(roots);
    fprintf(stderr, "test_doubles passed\n");
}


void test_strings(int argc, char *argv[])
{
    da_t *args = da_new_s();
    da_setcap(args, argc);
    for (int i = 0; i < argc; ++i)
        da_append_s(args, argv[i]);
    for (int i = 0; i < da_len(args); ++i)
        assert(!strcmp(da_get_s(args, i), argv[i]));
    da_free(args);
    fprintf(stderr, "test_strings passed\n");
}


void test_ints(void)
{
    da_t *fibs = da_new_i();
    da_setcap(fibs, NUM_ITERS);
    da_append_i(fibs, 0);
    da_append_i(fibs, 1);
    for (int i = 2; i < NUM_ITERS; ++i)
        da_append_i(fibs, da_get_i(fibs, i-1) + da_get_i(fibs, i-2));
    for (int i = 2; i < NUM_ITERS; ++i)
        assert(da_get_i(fibs, i) == da_get_i(fibs, i-1) + da_get_i(fibs, i-2));
    da_free(fibs);
    fprintf(stderr, "test_ints passed\n");
}


void test_ulongs(void)
{
    const int iters = 22;
    da_t *facts = da_new_ul();
    da_setcap(facts, iters);
    da_append_ul(facts, 1);
    for (int i = 1; i < iters; ++i)
        da_append_ul(facts, i * da_get_ul(facts, i-1));
    for (int i = 1; i < iters; ++i)
        assert(da_get_ul(facts, i) == da_get_ul(facts, i-1) * i);
    da_free(facts);
    fprintf(stderr, "test_ulongs passed\n");
}


void test_structs(void)
{
    typedef struct { double x; double y; } vec2_t;
    DA_DEF_SPEC(v2, vec2_t, NULL, NULL, NULL);
    /* const da_spec_t spec_v = {.size = sizeof(vec2_t)}; */
    const int sqrt_iters = sqrt(NUM_ITERS);
    da_t *vecs = da_new(&da_spec_v2);
    da_setcap(vecs, NUM_ITERS);
    for (int i = 0; i < sqrt_iters; ++i) {
        for (int j = 0; j < sqrt_iters; ++j) {
            vec2_t v = {i, j};
            da_append(vecs, &v);
        }
    }
    for (int i = 0; i < da_len(vecs); ++i) {
        vec2_t *vp = da_get(vecs, i);
        assert(vp->x == i / sqrt_iters);
        assert(vp->y == i % sqrt_iters);
    }
    da_free(vecs);
    fprintf(stderr, "test_structs passed\n");
}


void test_slices(void)
{
    da_t *nums = da_new_i();
    int a = 42, n = 10, b = a + n;
    da_setcap(nums, NUM_ITERS);
    for (int i = 0; i < NUM_ITERS; ++i)
        da_append_i(nums, i);
    da_t slice;
    int k = 3;
    while (k--) {
        da_slice(&slice, nums, a, b);
        assert(da_len(&slice) == n);
        for (int i = 0; i < da_len(&slice); ++i)
            da_set_i(&slice, i, da_get_i(&slice, i) * 2);
        for (int i = a; i < b; ++i)
            assert(da_get_i(nums, i) == i * 2);
        a *= 10;
        b *= 10;
        n *= 10;
    }
    da_free(nums);
    fprintf(stderr, "test_slices passed\n");
}


static int cmp_ip(const int *xp, const int *yp)
{
    return *xp - *yp;
}


void test_sort(void)
{
    da_t *nums = da_new_i();
    da_setcap(nums, NUM_ITERS);
    for (int i = 0; i < NUM_ITERS; ++i)
        da_append_i(nums, rand());
    da_sort(nums, (da_cmp_func_t *)cmp_ip);
    for (int i = 0, last = -1; i < NUM_ITERS; ++i) {
        int this = da_get_i(nums, i);
        assert(last <= this);
        last = this;
    }
    da_free(nums);
    fprintf(stderr, "test_sort passed\n");
}


int main(int argc, char *argv[])
{
    da_default_cap = DEFAULT_CAP;
    da_realloc = _realloc;
    test_doubles();
    test_floats();
    test_ints();
    test_slices();
    test_sort();
    test_strings(argc, argv);
    test_structs();
    test_ulongs();
    fprintf(stderr, "num allocs: %zu\n", da_num_allocs);
    fprintf(stderr, "num bytes alloced: %zukb\n", da_bytes_alloced / 1024);
    return 0;
}

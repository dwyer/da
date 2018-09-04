#ifndef __DA_UTILS__
#define __DA_UTILS__


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
    extern _DA_DEF_NEW(suf, T) \
    extern _DA_DEF_INIT(suf, T) \
    extern _DA_DEF_GET(suf, T) \
    extern _DA_DEF_SET(suf, T) \
    extern _DA_DEF_POP(suf, T) \
    extern _DA_DEF_APPEND(suf, T)


#define DA_DEF_HELPERS(suf, T) \
    DA_DEF_HELPERS_EX(suf, T, NULL, NULL, NULL)

#endif

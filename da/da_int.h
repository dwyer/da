#ifndef __DA_INT_H__
#define __DA_INT_H__

#include "da_util.h"


DA_DECL_HELPERS(c, char)
DA_DECL_HELPERS(d, double)
DA_DECL_HELPERS(f, float)
DA_DECL_HELPERS(i, int)
DA_DECL_HELPERS(l, long)
DA_DECL_HELPERS(ll, long long)
DA_DECL_HELPERS(uc, unsigned char)
DA_DECL_HELPERS(ui, unsigned int)
DA_DECL_HELPERS(ul, unsigned long)
DA_DECL_HELPERS(ull, unsigned long long)


#if DA_STDINT
#include <stdint.h>
DA_DECL_HELPERS(i8, int8_t)
DA_DECL_HELPERS(i16, int16_t)
DA_DECL_HELPERS(i32, int32_t)
DA_DECL_HELPERS(i64, int64_t)
DA_DECL_HELPERS(u8, uint8_t)
DA_DECL_HELPERS(u16, uint16_t)
DA_DECL_HELPERS(u32, uint32_t)
DA_DECL_HELPERS(u64, uint64_t)
#endif

#endif

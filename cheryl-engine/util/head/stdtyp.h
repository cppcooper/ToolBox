#ifndef __COMMON_STDTYP_H__
#define __COMMON_STDTYP_H__

#include <cstdint>
#include <climits>

#include <typeinfo>
#include <type_traits>
#include <limits>

//using size_t = std::size_t;
//#ifndef NULL
//#  define NULL nullptr
//#endif

#include <string>

typedef uint8_t         uint8   ;
typedef  int8_t         sint8   ;
typedef uint16_t        uint16  ;
typedef  int16_t        sint16  ;
typedef uint32_t        uint32  ;
typedef  int32_t        sint32  ;
typedef uint64_t        uint64  ;
typedef  int64_t        sint64  ;
typedef uintmax_t       uintMax ;
typedef  intmax_t       sintMax ;
typedef char            chr     , *str;
typedef const char     *cstr    ;
typedef const char     *const     cstrc;
typedef       char     *const     strc;

typedef intptr_t        sptr    ;
typedef uintptr_t       uptr    ;
typedef void           *rptr    ;
typedef size_t          msize   ;

#endif

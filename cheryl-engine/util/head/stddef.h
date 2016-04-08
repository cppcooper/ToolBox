#ifndef __E_STDDEF_H__
#define __E_STDDEF_H__

#include "head/platform.h"

#define UNUSED(x) (void)x

#if (E_COMPILER==COMP_MSVC) && (E_COMPILER_VER < 19)
#  define constexpr_
#  define static_assert_constexpr(...)
#  define alwaysinline inline __forceinline
#  define noinline     __declspec(noinline)
#elif (E_COMPILER==COMP_MSVC)
#  define constexpr_ constexpr
#  define static_assert_constexpr(...) static_assert(__VA_ARGS__)
#  define alwaysinline inline __forceinline
#  define noinline     __declspec(noinline)
#elif (E_COMPILER==COMP_GCC) || (E_COMPILER==COMP_CLANG)
#  define constexpr_ constexpr
#  define static_assert_constexpr(...) static_assert(__VA_ARGS__)
#  define alwaysinline inline __attribute__((always_inline))
#  define noinline     __attribute__((noinline)) 
#else
#  define constexpr_ constexpr
#  define static_assert_constexpr(...) static_assert(__VA_ARGS__)
#  define alwaysinline
#  define noinline
#endif

#if ((E_COMPILER==COMP_GCC) || (E_COMPILER==COMP_CLANG)) && (E_LANGUAGE < LANG_14)
   namespace std {
      template <bool cond, typename a, typename b>
      class conditional;

      template <bool cond, typename a>
      class enable_if;

      template <bool cond, typename a, typename b>
      using conditional_t = typename std::conditional<cond,a,b>::value;

      template <bool cond, typename a>
      using enable_if_t = typename std::enable_if<cond,a>::value;
   }
#endif

#if ((E_OS==OS_WIN32) || (E_OS==OS_WIN64)) && (E_COMPILER==COMP_MSVC)
#   define CONVENTION_STDCALL  __stdcall          // Callee cleans up
#   define CONVENTION_CDECL    __cdecl            // Caller cleans up
#   define CONVENTION_THISCALL __thiscall         
#   define CONVENTION_FASTCALL __fastcall
#   define CONVENTION_VECTOR   __vectorcall
#   define CONVENTION_DEFAULT
#   define CONVENTION_BASIC    CONVENTION_STDCALL // APIENTRY / WINAPI.
#elif (E_PLATFORM!=PLAT_X64) && ((E_COMPILER==COMP_GCC) || (E_COMPILER==COMP_CLANG))
#   define CONVENTION_STDCALL  __attribute__((stdcall))
#   define CONVENTION_CDECL    __attribute__((cdecl))
#   define CONVENTION_THISCALL __attribute__((thiscall))
#   define CONVENTION_FASTCALL __attribute__((fastcall))
#   define CONVENTION_VECTOR   
// TODO: detect BASIC based on OS
#   define CONVENTION_DEFAULT
#   define CONVENTION_BASIC    CONVENTION_STDCALL
#elif (E_PLATFORM==PLAT_X64) && ((E_COMPILER==COMP_GCC) || (E_COMPILER==COMP_CLANG))
#   define CONVENTION_STDCALL  __attribute__((stdcall))
#   define CONVENTION_CDECL    __attribute__((cdecl))
#   define CONVENTION_THISCALL __attribute__((thiscall))
#   define CONVENTION_FASTCALL __attribute__((fastcall))
#   define CONVENTION_VECTOR
#   define CONVENTION_DEFAULT
#   define CONVENTION_BASIC    CONVENTION_STDCALL
#else
#   define CONVENTION_STDCALL 
#   define CONVENTION_CDECL   
#   define CONVENTION_THISCALL
#   define CONVENTION_FASTCALL
#   define CONVENTION_VECTOR   
#   define CONVENTION_DEFAULT
#   define CONVENTION_BASIC   
#   if (E_PLATFORM==PLAT_X64)
#      error "Conventions are not known for this OS/Compiler!"
#   endif
#endif

#ifdef _
#  undef _
#endif

#if E_OS == OS_WINDOWS
#  define DEBUG_CONSOLEOUT       (1ull<<63)
#  define DEBUG_REGIONMEM_CLEAR  (1ull<<62)
#  define DEBUG_REGIONMEM_ASSERT (1ull<<61)
#endif
#define DEBUG_ALL (-1ll)
#undef x

#if E_COMPILER == COMP_MSVC
#  pragma warning(push)
#  pragma warning(disable:4668) // eval to 0
#endif

#if defined(DEBUG) || defined(_DEBUG)
#  if !DEBUG
#     ifdef DEBUG
#        undef DEBUG
#     endif
#     define DEBUG (DEBUG_ALL)
#  endif
#endif

#if E_COMPILER == COMP_MSVC
#  pragma warning(pop)
#endif

#if defined(UNICODE) || defined(_UNICODE)
#  define _(x) L##x
#else
#  define _(x) x
#endif

#endif


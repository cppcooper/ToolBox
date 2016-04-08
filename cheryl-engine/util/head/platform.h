#ifndef __E_PLATFORM_H__
#define __E_PLATFORM_H__

// NOTE: Generally you shouldn't use the OS_WIN32 or OS_LIN64 type entries.
//       they're just shims for broken code from elsewhere.

#define OS_UNKNOWN   (0)
//#define OS_WIN32     (1)
//#define OS_WIN64     (2)
#define OS_WINDOWS   (1)
#define OS_WIN32     (1) && ((E_PLATFORM==PLAT_X32)||(E_PLATFORM==PLAT_ARM32))
#define OS_WIN64     (1) && ((E_PLATFORM==PLAT_X64)||(E_PLATFORM==PLAT_ARM64))
//#define OS_LIN32     (3)
//#define OS_LIN64     (4)
#define OS_LINUX     (3)
#define OS_LIN32     (3) && ((E_PLATFORM==PLAT_X32)||(E_PLATFORM==PLAT_ARM32))
#define OS_LIN64     (3) && ((E_PLATFORM==PLAT_X64)||(E_PLATFORM==PLAT_ARM64))

#define OS_OSX       (5)
#define OS_OSXPOD    (6)

#define COMP_UNKNOWN (0)
#define COMP_MSVC    (1)
#define COMP_CLANG   (2)
#define COMP_GCC     (3)
#define COMP_MINGW   (4)

#define PLAT_UNKNOWN (0)
#define PLAT_X64     (1)
#define PLAT_X32     (2)
#define PLAT_ARM32   (3)
#define PLAT_ARM64   (4)

#define LANG_98      (199711L)
#define LANG_11      (201103L)
#define LANG_14      (201402L)

#define E_LANGUAGE (__cplusplus)


#if defined(_MSC_VER)
#  define E_COMPILER      (COMP_MSVC)
#  define E_COMPILER_VER  (_MSC_VER/100)
#  if E_COMPILER_VER > 17
#     undef  E_LANGUAGE
#     define E_LANGUAGE (LANG_14)
#  elif E_COMPILER_VER > 16
#     undef  E_LANGUAGE
#     define E_LANGUAGE (LANG_11)
#  endif
#elif defined(__clang__)
#  define E_COMPILER      (COMP_CLANG)
#  define E_COMPILER_VER  (__clang_major__)
#elif defined(__GNUC__)
#  define E_COMPILER      (COMP_GCC)
#  define E_COMPILER_VER  (__GNUC__)
#else
#  define E_COMPILER      (COMP_UNKNOWN)
#  define E_COMPILER_VER  (0xFFFFFFFF)
#endif 

#if (defined(_WIN32) && defined(_M_IX86)) || defined(__WIN32__)
#  define E_OS   (OS_WINDOWS) // (OS_WIN32)
#elif defined(_WIN64)
#  define E_OS   (OS_WINDOWS) // (OS_WIN64)
#elif defined(__gnu_linux__) 
#  if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#     define E_OS (OS_LINUX) // (OS_LIN64)
#  elif defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
#     define E_OS (OS_LINUX) // (OS_LIN32)
#  endif
#else
#  define E_OS   (OS_UNKNOWN)
#endif

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
#  define E_PLATFORM (PLAT_X64)
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86)
#  define E_PLATFORM (PLAT_X32)
#else
#  define E_PLATFORM (PLAT_UNKNOWN)
#endif

#if E_OS==OS_WIN32 || E_OS==OS_WIN64
#  include "targetver.h"
#  if E_COMPILER==COMP_MSVC 
//#     pragma once
#     pragma warning(disable:4628) // Digraphs not supported with -Ze
#     pragma warning(disable:4514) // unreferenced inline function has been removed
#     pragma warning(disable:4820) // bytes padding added after data member
#     pragma warning(disable:4710) // function not inlined
#     pragma warning(disable:4435) // Constructor Displacement may cause binary incompatibility
// http://stackoverflow.com/questions/15505023/suppress-anonymous-structs-warning-with-clang-fms-extensions-doesnt-work
#     pragma warning(disable:4201) // unnamed structs. Enable on GCC with -fms-extensions
#     pragma warning(disable:4355) // use of incomplete 'this' in class init list
#  endif
#endif

#endif


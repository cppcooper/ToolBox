#ifndef __SYSLIBS_H__
#define __SYSLIBS_H__

#include "head/platform.h"

#if (E_OS==OS_WIN32) || (E_OS==OS_WIN64)
#  if E_COMPILER==COMP_MSVC
#     pragma warning(push)
#     pragma warning(disable:4668) // not defined as a preprocessor macro
#  endif
#  include <WinSock2.h>
#  include <Windows.h>
#  ifdef min
#     undef min
#  endif
#  ifdef max
#     undef max
#  endif
#  if E_COMPILER==COMP_MSVC
#     pragma warning(pop)
#  endif
#endif

#if (E_OS==OS_LINUX)
#  include <unistd.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <fcntl.h>
#  include <sys/mman.h>
#endif

#endif


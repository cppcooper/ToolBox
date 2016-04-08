#ifndef __E_COMMON_H__
#define __E_COMMON_H__

#include "head/platform.h"

#if E_COMPILER==COMP_MSVC
#  pragma warning(push)
#  pragma warning(disable:4350) // behavior change
#  define _CRT_SECURE_NO_WARNINGS
#endif

#include "head/stddef.h"
#include "head/stdtyp.h"
#include "head/stdlibs.h"

#if E_COMPILER==COMP_MSVC
#  pragma warning(pop)
#endif

#include "head/syslibs.h"
#include "head/systyp.h"
//#include "extlibs.h"

//#include "util/hash.h"            // util::hash::

//#include "util/popcount.h"        // util::     // Population count, compile and run time
//#include "util/bits.h"            // util::     // Bit tricks

//#include "util/extint.h"          // util::     // Flexible/variable-width integers
//#include "util/highresTimer.h"    // util::     // High resolution timers/counters
//#include "util/threaded.h"        // util::     // Flexible platform-independent C++ threading

//#include "util/factories.h"       // util::pattern::factory::

//#include "util/alt.h"

#endif 

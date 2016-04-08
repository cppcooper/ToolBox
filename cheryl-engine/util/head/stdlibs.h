#ifndef __COMMON_STDHEAD_H__
#define __COMMON_STDHEAD_H__

#include "head/platform.h"

#include <cstdarg>
#include <cstdlib>
#include <cstddef>
#include <ctime>
#include <cstring>
#include <cstdio>

#if E_COMPILER==COMP_MSVC
#  include <intrin.h>
#endif

#include <memory>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <chrono>

#if E_COMPILER == COMP_MSVC
#  pragma warning(push)
#  pragma warning(disable:4265)
#endif
#include <mutex>
#if E_COMPILER == COMP_MSVC
#  pragma warning(pop)
#endif
//#include <thread>
#include <atomic>

#include <algorithm>
#include <array>
#include <tuple>
#include <vector>
#include <map>
#include <set>

#endif

#ifndef _INTX_H_
#define _INTX_H_

#ifdef WIN32
using int8 = __int8;
using uint8 = unsigned __int8;
using int16 = __int16;
using uint16 = unsigned __int16;
using int32 = __int32;
using uint32 = unsigned __int32;
using int64 = __int64;
using uint64 = unsigned __int64;
#else
using int8 = char;
using uint8 = unsigned char;
using int16 = short;
using uint16 = unsigned short;
using int32 = int;
using uint32 = unsigned int;
using int64 = long long;
using uint64 = unsigned long long;
#endif

#endif
#ifndef _MY_UTILITIES_H
#define _MY_UTILITIES_H
#include <cassert>
#include <cmath>

//#pragma comment (lib,"my_utilities.lib")

template<typename T>
inline T LowBitMask( size_t LowBits )
{
	size_t total_bits = sizeof( T ) * 8;
	assert( LowBits != 0 && LowBits < total_bits );
	return (T)( 1 << ( total_bits - LowBits ) ) - 1;
}

template<typename T>
inline T GetHighBits( T value, unsigned char MaskBits )
{
	return value & ~LowBitMask<T>( MaskBits );
}

template<typename T>
inline T GetLowBits( T value, unsigned char MaskBits )
{
	return value & LowBitMask<T>( MaskBits );
}

inline long long MergeIntegers( int A, int B )
{
	union
	{
		struct
		{
			int A;
			int B;
		};
		long long value;
	}ReturnVal;
	ReturnVal.A = A;
	ReturnVal.B = B;
	return ReturnVal.value;
}

#endif
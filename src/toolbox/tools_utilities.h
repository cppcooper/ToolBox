#ifndef _MY_UTILITIES_H
#define _MY_UTILITIES_H
#include <cassert>
#include <cmath>

#ifdef _DEBUG
#pragma comment (lib,"tools_utilities_Debug.lib")
#else
#pragma comment (lib,"tools_utilities_Release.lib")
#endif

template<typename T>
inline T LowBitMask( size_t LowBits )
{
    size_t total_bits = sizeof( T ) * 8;
    assert( LowBits != 0 && LowBits < total_bits );
    return (T)( 1 << LowBits ) - 1;
}

template<typename T>
inline T HighBitMask( size_t HighBits )
{
    size_t total_bits = sizeof( T ) * 8;
    assert( HighBits != 0 && HighBits < total_bits );
    return ~( (T)( 1 << ( total_bits - HighBits ) ) - 1 );
}

template<typename T>
inline T GetHighBits( T Value, unsigned char MaskBits )
{
    return Value & HighBitMask<T>( MaskBits );
}

template<typename T>
inline T GetLowBits( T Value, unsigned char MaskBits )
{
    return Value & LowBitMask<T>( MaskBits );
}

template<typename T>
inline T IncrementAtBit( T Value, unsigned char bit )
{
    assert( bit != 0 );
    return Value + ( 1 << ( bit - 1 ) );
}

template<typename T>
inline T DecrementAtBit( T Value, unsigned char bit )
{
    assert( bit != 0 );
    return Value - ( 1 << ( bit - 1 ) );
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

inline unsigned long long MergeIntegers( unsigned int A, unsigned int B )
{
    union
    {
        struct
        {
            unsigned int A;
            unsigned int B;
        };
        unsigned long long value;
    }ReturnVal;
    ReturnVal.A = A;
    ReturnVal.B = B;
    return ReturnVal.value;
}

#endif
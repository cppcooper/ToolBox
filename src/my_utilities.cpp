#include "../my_utilities.h"

long long MergeIntegers( int A, int B )
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
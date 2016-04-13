#pragma once

#include <bitset>

union InputContext
{
	unsigned int value;
	#ifdef _MSC_VER
	struct{
		std::bitset<32> mask;
	};
	#else
	std::bitset<32> mask;
	#endif

	InputContext();
	bool operator==( const InputContext& other );
	bool operator!=( const InputContext& other );
};
#pragma once

#include <int_typedefs.h>
#include <bitset>

union InputContext
{
	uint32 value;
	std::bitset<32> mask;

	InputContext();
	bool operator==( const InputContext& other );
	bool operator!=( const InputContext& other );
};
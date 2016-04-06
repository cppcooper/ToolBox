#pragma once

#include <bitset>

union InputContext
{
	unsigned int value;
	struct {
		std::bitset<32> mask;
	};

	InputContext();
	bool operator==( const InputContext& other );
	bool operator!=( const InputContext& other );
};
#pragma once

#include <string>
#include "../../../3rdparty/Steamworks/public/steam/steam_api.h"

class InputStateDigital
{
public:
	virtual bool poll() = 0;
};

class InputStateAnalog
{
public:
	virtual void poll( double& x, double& y ) = 0;
};
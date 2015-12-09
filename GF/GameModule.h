#ifndef _GAMEMODULE_H_
#define _GAMEMODULE_H_

#include "ViewPort.h"

class GameModule
{
public:
	virtual void Init() = 0;
	virtual void Deinit() = 0;

	virtual void Process() = 0;
	virtual void Update( double& seconds ) = 0;
	virtual void PostProcess() = 0;
	
	virtual void Buffer() = 0;
	virtual void Draw() = 0;
};

#endif
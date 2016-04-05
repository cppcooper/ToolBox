#ifndef _GAMEMODULE_H_
#define _GAMEMODULE_H_

class GameModule
{
public:
	virtual void Init() {}
	virtual void Deinit() {}

	virtual void Process() {}
	virtual void Update(double& seconds) {}
	virtual void PostProcess() {}
	
	virtual void Buffer() {}
	virtual void Draw() {}
};

#endif
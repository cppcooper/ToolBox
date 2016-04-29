#pragma once
#include<vector>
#include "InputContext.h"

class InputBinding;
class InputMapper
{
	friend class InputSystem;
private:
	InputContext m_Context;
	std::vector<InputBinding*> m_Bindings;
public:
	void Poll();
};
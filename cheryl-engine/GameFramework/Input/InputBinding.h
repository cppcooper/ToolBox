#pragma once

#include <functional>
#include <int_typedefs.h>

class InputBinding
{
protected:
	uint32 m_Priority = -1;
public:
	virtual void poll() = 0;
};


class InputStateDigital;
class InputBindingDigital : public InputBinding
{
private:
	std::function<void()> m_ActionCallback;
	InputStateDigital* m_State = nullptr;

public:
	InputBindingDigital( InputStateDigital* state, std::function<void()> action, uint32 priority );
	void poll() override;
};


class InputStateAnalog;
class InputBindingAnalog : public InputBinding
{
private:
	std::function<void(double, double)> m_RangeCallback;
	InputStateAnalog* m_State = nullptr;

public:
	InputBindingAnalog( InputStateAnalog* state, std::function<void( double, double )> action, uint32 priority );
	void poll() override;
};
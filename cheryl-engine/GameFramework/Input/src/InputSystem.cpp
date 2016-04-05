#include "../InputSystem.h"

void InputSystem::Init()
{
	m_ActiveControllers = SteamController()->GetConnectedControllers( m_SteamControllers );

	//ControllerActionSetHandle_t ActionHandle = SteamController()->GetActionSetHandle("");
}

void InputSystem::Process()
{

}
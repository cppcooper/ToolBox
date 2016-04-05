#pragma once

#include "../../../3rdparty/Steamworks/public/steam/steam_api.h"
#include "../GameModule.h"
#pragma comment (lib, "3rdparty/Steamworks/steam_api.lib")

class InputSystem : public GameModule
{
private:
	uint32 m_ActiveControllers = 0;
	ControllerHandle_t* m_SteamControllers = nullptr;
protected:
public:
	void Init() final override;
	void Process() final override;
};
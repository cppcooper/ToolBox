#ifndef GAME_H_
#define GAME_H_

//#include "../../3rdparty/Steamworks/public/steam/steam_api.h"
//#pragma comment (lib, "3rdparty/Steamworks/steam_api.lib")

#include "../GLEngine/GLEngine.h"
#include "../AssetFaculties/AssetFaculties.h"

#include "GameModule.h"
#include "ControlModule.h"

#ifdef _DEBUG
#pragma comment (lib,"Cheryl-Engine/GameFramework_Debug.lib")
#else
#pragma comment (lib,"Cheryl-Engine/GameFramework_Release.lib")
#endif


#include <vector>

class Game
{
private:
	Asset_Faculties& m_Faculties = Asset_Faculties::Instance();
	ControlModule& Controls = ControlModule::Instance();
	glEngine& m_glEngine = glEngine::Instance();

	std::vector<GameModule*> m_Modules;
	bool m_Initialized = false;
	Game(){ Attach( &Controls ); }

protected:
	/*Update & Draw are not guaranteed to have a 1:1 execution ratio*/
	void Update( double& seconds );
	/*Draw & Update are not guaranteed to have a 1:1 execution ratio*/
	void Draw();

	void PressKey( int& key, int& scancode, int& action, int& mod );
	void PressMouse( int& button, int& action, int& mod );
	void SetCursor( double& x, double& y );

public:
	static Game& Instance()
	{
		static Game instance;
		return instance;
	}
	void Init();
	void Deinit();
	void Attach( GameModule* module );
	void Detach( GameModule* module );
	void Run() const;
};

#endif

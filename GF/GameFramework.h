#ifndef GAME_H_
#define GAME_H_

#include <GFX\gl_engine.h>

#include "game_faculties.h"
#include "GameModule.h"
#include "ControlModule.h"
#pragma comment (lib,"GF/GameFramework.lib")

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
	//TODO: void Detach( GameModule* module );
	void Run() const;
};

#endif

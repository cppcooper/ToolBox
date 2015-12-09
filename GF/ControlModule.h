#ifndef _INPUT_H_
#define _INPUT_H_

#include "GameModule.h"

#include <mutex>
#include <thread>
#include <vector>
#include <map>
#include <functional>


//This class SETS the association between controls and game actions
class ControlModule : public GameModule
{
private:
	struct MState
	{
		double cursor_x;
		double cursor_y;
		int button;
	} mouse_state;
	std::vector<MState> m_MouseInput;
	std::vector<int> m_KeysInput;

	std::mutex m_InputMutex;
	std::mutex m_ActionMutex;
	//TODO: Implement methodology for reconfiguring controls
	std::multimap<int, std::function<void()>> Key_Action_Map;
	std::multimap<int, std::function<void( MState state )>> Button_Action_Map;
	std::vector<std::function<void( double x, double y )>> Cursor_Readers;
	ControlModule(){}
	~ControlModule(){}

public:
	static ControlModule& Instance();
	void Bind_Cursor( std::function<void( double x, double y )> reader );
	void Bind_Button( int button, std::function<void( MState state )> action );
	void Bind_Key( int key, std::function<void()> action );

	void MoveCursor( double x, double y );
	void QueueButton( int button );
	void QueueKey( int key );

	void Process() override;

	void Init() final override {}
	void Draw() final override {}
	void Deinit() final override {}
	void Buffer() final override {}
	void PostProcess() final override {}
	void Update( double& seconds ) final override {}
};

#endif

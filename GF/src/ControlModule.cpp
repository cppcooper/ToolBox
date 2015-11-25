#include "../ControlModule.h"

#include <GFX\OpenGL_Headers.h>


ControlModule& ControlModule::Instance()
{
	static ControlModule instance;
	return instance;
}

void ControlModule::Bind_Cursor( std::function<void( double x, double y )> &reader )
{
	m_ActionMutex.lock();
	Cursor_Readers.push_back( reader );
	m_ActionMutex.unlock();
}

void ControlModule::Bind_Button( int button, std::function<void( MState state )> &action )
{
	m_ActionMutex.lock();
	Button_Action_Map.emplace( button, action );
	m_ActionMutex.unlock();
}

void ControlModule::Bind_Key( int key, std::function<void()> &action )
{
	m_ActionMutex.lock();
	Key_Action_Map.emplace( key, action );
	m_ActionMutex.unlock();
}


void ControlModule::MoveCursor( double x, double y )
{
	m_InputMutex.lock();
	mouse_state.cursor_x = x;
	mouse_state.cursor_y = y;
	m_InputMutex.unlock();
	for ( auto func : Cursor_Readers )
	{
		func( x, y );
	}
}

void ControlModule::QueueButton( int button )
{
	m_InputMutex.lock();
	mouse_state.button = button;
	m_MouseInput.push_back( mouse_state );
	m_InputMutex.unlock();
}

void ControlModule::QueueKey( int key )
{
	m_InputMutex.lock();
	m_KeysInput.push_back( key );
	m_InputMutex.unlock();
}

//TODO: Implement additional methodology for real-time processing
void ControlModule::Process()
{
	m_InputMutex.lock();
	m_ActionMutex.lock();
	
	for ( auto k : m_KeysInput )
	{
		auto actions = Key_Action_Map.equal_range( k );
		for ( auto it = actions.first; it != actions.second; ++it )
		{
			it->second();
		}
	}
	m_KeysInput.clear();

	for ( auto m : m_MouseInput )
	{
		auto actions = Button_Action_Map.equal_range( m.button );
		for ( auto it = actions.first; it != actions.second; ++it )
		{
			it->second( m );
		}
	}
	m_MouseInput.clear();
	
	m_InputMutex.unlock();
	m_ActionMutex.unlock();
}

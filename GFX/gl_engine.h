/*
v1.0.1
The MIT License (MIT)

Copyright (c) <2015> <Josh S, Cooper>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.*/


#ifndef ENGINE3D_H
#define ENGINE3D_H
#ifdef _WIN32
	#define WIN32_EXTRA_LEAN
	#include <Windows.h>
#endif

#include "OpenGL_Headers.h"

#ifdef _DEBUG
#pragma comment (lib,"GFX/GL_Engine/glEngine_Debug.lib")
#else
#pragma comment (lib,"GFX/GL_Engine/glEngine_Release.lib")
#endif
//Threading Libraries
#include <thread>
#include <mutex>
#include <atomic>



namespace GL_Engine
{
	enum class graphics { R2D = 0, R3D };
	enum class window { DECORATEDWINDOW = 1, FULLSCREEN, BORDERLESSFULLSCREEN };
}

extern void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
extern void mouse_button_callback( GLFWwindow* window, int button, int action, int mods );
extern void cursor_position_callback( GLFWwindow* window, double x, double y );
extern void window_resize_callback( GLFWwindow* window, int width, int height );

class Screen
{
	friend class glEngine;
private:
	int m_Width = 0;
	int m_Height = 0;
	Screen(){}
	void Resize( int width, int height ){
		m_Width = width;
		m_Height = height;
	}
protected:
	static Screen& Instance(){
		static Screen instance;
		return instance;
	}
public:
	static int Width() {
		return Instance().m_Width;
	}
	static int Height() {
		return Instance().m_Height;
	}
};
/* glEngine is a Game Model framework 
* Input, State Updates, Output
*/
class glEngine
{
private:
	HDC m_currentDC;
	HGLRC m_currentContext;

	bool Run_Threads = false;
	bool ManualBufferSwap = false;
	std::thread Game_Update_thread;
	std::thread Game_Draw_thread;
	std::function<void( double& seconds )> Update_f;
	std::function<void()> Draw_f;

public:
	std::function<void( int& key, int& scancode, int& action, int& mod )> key_callback_f;
	std::function<void( int& button, int& action, int& mod )> mouse_button_callback_f;
	std::function<void( double& x, double& y )> cursor_position_callback_f;

	GLFWwindow* m_window;
	float m_nearplane;
	float m_farplane;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

private:
	friend class Screen;
	GL_Engine::graphics m_gMode;
	GL_Engine::window m_wMode;
	Screen& m_Screen = Screen::Instance();
	bool m_ScreenSizeLock = false;
	GLclampf m_red = 0.8f;
	GLclampf m_blue = 0.6f;
	GLclampf m_green = 0.7f;
	GLclampf m_alpha = 0.0f;

protected:
	glEngine( GL_Engine::window wMode = GL_Engine::window::DECORATEDWINDOW, int width = 1920, int height = 1080 );
	void Update();
	void Draw();

public:	
	~glEngine();
	void ShowCursor( bool show );

	void SetMode( GL_Engine::graphics newMode );
	void set_Draw_f( std::function<void()> Draw_f );
	void set_Update_f( std::function<void( double& seconds )> Update_f );
	bool Init();
	void Run();
	void Quit();
	
	void DisableBufferSwap( bool disable = true );
	void LockScreenSize();
	void UnlockScreenSize();
	void Resize( int width, int height );
	void SetClearColor( float r, float g, float b, float a = 0.0f );

	static glEngine& Instance()
	{
		static glEngine engine( GL_Engine::window::DECORATEDWINDOW, 1000, 600 );
		return engine;
	}
};


#endif
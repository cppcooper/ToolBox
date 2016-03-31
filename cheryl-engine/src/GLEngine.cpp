#include "../GLEngine.h"
#include "../../tools_bench.h"


void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	glEngine::Instance().key_callback_f( key, scancode, action, mods );
}

void cursor_position_callback( GLFWwindow* window, double x, double y )
{
	glEngine::Instance().cursor_position_callback_f( x, y );
}

void mouse_button_callback( GLFWwindow* window, int button, int action, int mods )
{
	glEngine::Instance().mouse_button_callback_f( button, action, mods );
}

void window_resize_callback( GLFWwindow* window, int width, int height )
{
	glEngine::Instance().Resize( width, height );
}

glEngine::glEngine( GL_Engine::window windowMode, int width, int height )
{
	m_wMode = windowMode;
	m_Screen.m_Width = width;
	m_Screen.m_Height = height;

	m_nearplane = 0.1f;
	m_farplane = 10000.f;
}

/// Will only be run from a new thread
//Method executes a pointer to the update function in a loop
void glEngine::Update()
{
	time_lord timer;
	timer.set_TimePoint_A();
	timer.set_TimePoint_B();
	double seconds;
	while ( Run_Threads )
	{
		seconds = timer.Elapsed_seconds();
		timer.set_TimePoint_A();
		Update_f( seconds );
		timer.set_TimePoint_B();
	}
}

/// Will only be run from a new thread
//Method executes a pointer to the update function in a loop
void glEngine::Draw()
{
	///Makes this thread the current context in which OpenGL rendering can occur
	wglMakeCurrent( m_currentDC, m_currentContext );

	glClearColor( m_red, m_green, m_blue, m_alpha );
	while ( Run_Threads )
	{
		if ( !ManualBufferSwap )
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		Draw_f();
		if ( !ManualBufferSwap )
			glfwSwapBuffers( m_window );
	}
	///We need to disassociate this thread with OpenGL's rendering
	wglMakeCurrent( 0, 0 );
}


glEngine::~glEngine()
{
	///If the threads are currently running then we need to stop them
	if ( Run_Threads )
	{
		Quit();
	}
}

void glEngine::ShowCursor( bool show )
{
	if ( show )
	{
		glfwSetInputMode( m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
	}
	else
	{
		glfwSetInputMode( m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN );
	}
}

//Basically sets the projection matrix required for rendering in "newMode"
void glEngine::SetMode( GL_Engine::graphics newMode )
{
	if ( m_gMode == newMode ) return;

	m_gMode = newMode;

	if ( m_gMode == GL_Engine::graphics::R3D )
	{
		/// Enable Depth Testing for 3D!
		glEnable( GL_DEPTH_TEST );

		///3D perspective projection
		m_projectionMatrix = glm::mat4( 1.f ) * glm::perspective( 45.0f, (GLfloat)( m_Screen.Width() ) / (GLfloat)( m_Screen.Height() ), m_nearplane, m_farplane );
	}
	else
	{
		/// Disable Depth Testing for 2D!
		glDisable( GL_DEPTH_TEST );

		///2d orthographic projection
		m_projectionMatrix = glm::mat4( 1.f ) * glm::ortho( 0.f, (float)m_Screen.Width(), 0.f, (float)m_Screen.Height(), 0.f, 1.f );
	}

}

//Method sets the update function to be called every cycle
void glEngine::set_Update_f( std::function<void( double& seconds )> Update_f )
{
	this->Update_f = Update_f;
}

//Method sets the draw function to be called every cycle
void glEngine::set_Draw_f( std::function<void()> Draw_f )
{
	this->Draw_f = Draw_f;
}

//Method initializes OpenGL for rendering to a window/viewport
bool glEngine::Init()
{
	/// We need our GLFW function pointers to be assigned, if this process fails we cannot continue
	if ( !glfwInit() )
	{
		return false;
	}

	/// Here we query how much sampling is possible and set that to be used if possible
	GLint samples = 8;
	glGetIntegerv( GL_SAMPLES, &samples );
	if ( samples )
	{
		glEnable( GL_MULTISAMPLE );
	}
	glfwWindowHint( GLFW_SAMPLES, samples );

	GLFWmonitor** monitors;
	int count;

	monitors = glfwGetMonitors( &count );
	//TODO: Create Window Resizing method
	const GLFWvidmode* mode = glfwGetVideoMode( glfwGetPrimaryMonitor() );

	///Create a window of a particular type
	switch ( m_wMode )
	{
		case GL_Engine::window::FULLSCREEN:
		{
			m_window = glfwCreateWindow( mode->width, mode->height, "Fullscreen", glfwGetPrimaryMonitor(), NULL );
			m_Screen.m_Height = mode->height;
			m_Screen.m_Width = mode->width;
			break;
		}

		case GL_Engine::window::DECORATEDWINDOW:
		{
			m_window = glfwCreateWindow( m_Screen.Width(), m_Screen.Height(), "Decorated Window", NULL, NULL );
			break;
		}

		case GL_Engine::window::BORDERLESSFULLSCREEN:
		{
			glfwWindowHint( GLFW_DECORATED, false );

			glfwWindowHint( GLFW_RED_BITS, mode->redBits );
			glfwWindowHint( GLFW_GREEN_BITS, mode->greenBits );
			glfwWindowHint( GLFW_BLUE_BITS, mode->blueBits );
			glfwWindowHint( GLFW_REFRESH_RATE, mode->refreshRate );

			m_window = glfwCreateWindow( mode->width, mode->height, "Borderless Fullscreen", NULL, NULL );
			m_Screen.m_Height = mode->height;
			m_Screen.m_Width = mode->width;
			break;
		}
	}

	/// If creating the window failed we need to terminate
	if ( !m_window )
	{
		glfwTerminate();
		return false;
	}
	/// Associates this window with OpenGL's rendering (I believe)
	glfwMakeContextCurrent( m_window );

	/// Sets our input processing function, all input will be passed to this function
	//glfwSetScrollCallback( window, scroll_callback );
	glfwSetKeyCallback( m_window, key_callback );
	glfwSetCursorPosCallback( m_window, cursor_position_callback );
	glfwSetMouseButtonCallback( m_window, mouse_button_callback );
	glfwSetWindowSizeCallback( m_window, window_resize_callback );

	/// start GLEW extension handler
	glewExperimental = GL_TRUE;

	///Initialize OpenGL functions
	glewInit();
	const GLubyte* renderer = glGetString( GL_RENDERER ); /// get renderer string
	const GLubyte* version = glGetString( GL_VERSION ); /// version as a string
	///oLog( Level::Info ) << "Renderer: " << renderer;
	///oLog( Level::Info ) << "OpenGL version supported: " << version;

	m_projectionMatrix = glm::mat4( 1.f );
	m_viewMatrix = glm::mat4( 1.f );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );	///clear colour: r,g,b,a 	
	glfwSwapInterval( 1 ); ///cap FPS

	m_currentDC = wglGetCurrentDC();
	m_currentContext = wglGetCurrentContext();

	return true;
}

///Main Thread
//Method initiates the game (essentially)
void glEngine::Run()
{
	///Controls the threads to be started up soon
	Run_Threads = true;

	///We need to disassociate this thread with OpenGL's rendering
	wglMakeCurrent( 0, 0 );

	///Start our threads
	Game_Update_thread = std::thread( &glEngine::Update, this );
	Game_Draw_thread = std::thread( &glEngine::Draw, this );

	while ( !glfwWindowShouldClose( m_window ) )
	{
		///We are about to get keyboard input and other events
		///Polling for input events is the most important function of the engine so Polling is done here in the main thread.
		glfwPollEvents();
		std::this_thread::sleep_for( std::chrono::milliseconds( 75 ) );
	}
	Quit();
	///Makes this thread the current context in which OpenGL rendering can occur
	wglMakeCurrent( m_currentDC, m_currentContext );
	glfwTerminate();
}

//Method will terminate all running code
void glEngine::Quit()
{
	if ( Run_Threads )
	{
		///Controls threads
		Run_Threads = false;
		///Joins threads
		Game_Update_thread.join();
		Game_Draw_thread.join();

		///Closes window
		glfwSetWindowShouldClose( m_window, GL_TRUE );
	}
}

void glEngine::DisableBufferSwap( bool disable )
{
	ManualBufferSwap = disable;
}

void glEngine::LockScreenSize()
{
	m_ScreenSizeLock = true;
}

void glEngine::UnlockScreenSize()
{
	m_ScreenSizeLock = false;
}

void glEngine::Resize( int width, int height )
{
	//TODO: Recalculate projection matrix for GLSLPrograms
	if ( !m_ScreenSizeLock )
	{
		assert( width >= 0 && height >= 0 );
		const GLFWvidmode * mode = glfwGetVideoMode( glfwGetPrimaryMonitor() );
		width = width <= mode->width ? width : mode->width;
		height = height <= mode->height ? height : mode->height;
		glfwSetWindowSize( m_window, width, height );
		glViewport( 0, 0, width, height );
		m_Screen.Resize( width, height );
	}
	else
	{
		glfwSetWindowSize( m_window, m_Screen.Width(), m_Screen.Height() );
	}
}

void glEngine::SetClearColor( float r, float g, float b, float a )
{
	m_red = r;
	m_blue = b;
	m_green = g;
	m_alpha = a;
}

#include "../gl_engine.h"
#include "../../bench.h"


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


glEngine::glEngine( GL_Engine::window windowMode, int width, int height )
{
	wMode = windowMode;
	screenWidth = width;
	screenHeight = height;

	nearplane = 0.1f;
	farplane = 10000.f;
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
	wglMakeCurrent( currentDC, currentContext );

	while ( Run_Threads )
	{
		glClearColor( 0.8f, 0.6f, 0.7f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		Draw_f();
		glfwSwapBuffers( window );
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
		glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
	}
	else
	{
		glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN );
	}
}

//Basically sets the projection matrix required for rendering in "newMode"
void glEngine::SetMode( GL_Engine::graphics newMode )
{
	if ( gMode == newMode ) return;

	gMode = newMode;

	if ( gMode == GL_Engine::graphics::R3D )
	{
		/// Enable Depth Testing for 3D!
		glEnable( GL_DEPTH_TEST );

		///3D perspective projection
		projectionMatrix = glm::mat4( 1.f ) * glm::perspective( 45.0f, (GLfloat)( screenWidth ) / (GLfloat)( screenHeight ), nearplane, farplane );
	}
	else
	{
		/// Disable Depth Testing for 2D!
		glDisable( GL_DEPTH_TEST );

		///2d orthographic projection
		projectionMatrix = glm::mat4( 1.f ) * glm::ortho( 0.f, (float)screenWidth, 0.f, (float)screenHeight, 0.f, 1.f );
	}

}

//Method sets the update function to be called every tick
void glEngine::set_Update_f( std::function<void( double& seconds )> Update_f )
{
	this->Update_f = Update_f;
}

//Method sets the draw function to be called every tick
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
	const GLFWvidmode* mode = glfwGetVideoMode( glfwGetPrimaryMonitor() );

	///Create a window of a particular type
	switch ( wMode )
	{
		case GL_Engine::window::FULLSCREEN:
		{
			window = glfwCreateWindow( mode->width, mode->height, "Fullscreen", glfwGetPrimaryMonitor(), NULL );
			screenHeight = mode->height;
			screenWidth = mode->width;
			break;
		}

		case GL_Engine::window::DECORATEDWINDOW:
		{

			window = glfwCreateWindow( screenWidth, screenHeight, "Decorated Window", NULL, NULL );
			break;
		}

		case GL_Engine::window::BORDERLESSFULLSCREEN:
		{
			glfwWindowHint( GLFW_DECORATED, false );

			glfwWindowHint( GLFW_RED_BITS, mode->redBits );
			glfwWindowHint( GLFW_GREEN_BITS, mode->greenBits );
			glfwWindowHint( GLFW_BLUE_BITS, mode->blueBits );
			glfwWindowHint( GLFW_REFRESH_RATE, mode->refreshRate );

			window = glfwCreateWindow( mode->width, mode->height, "Borderless Fullscreen", NULL, NULL );
			screenHeight = mode->height;
			screenWidth = mode->width;
			break;
		}
	}

	/// If creating the window failed we need to terminate
	if ( !window )
	{
		glfwTerminate();
		return false;
	}
	/// Associates this window with OpenGL's rendering (I believe)
	glfwMakeContextCurrent( window );

	/// Sets our input processing function, all input will be passed to this function
	//glfwSetScrollCallback( window, scroll_callback );
	glfwSetKeyCallback( window, key_callback );
	glfwSetCursorPosCallback( window, cursor_position_callback );
	glfwSetMouseButtonCallback( window, mouse_button_callback );

	/// start GLEW extension handler
	glewExperimental = GL_TRUE;

	///Initialize OpenGL functions
	glewInit();
	const GLubyte* renderer = glGetString( GL_RENDERER ); /// get renderer string
	const GLubyte* version = glGetString( GL_VERSION ); /// version as a string
	///oLog( Level::Info ) << "Renderer: " << renderer;
	///oLog( Level::Info ) << "OpenGL version supported: " << version;

	projectionMatrix = glm::mat4( 1.f );
	viewMatrix = glm::mat4( 1.f );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );	///clear colour: r,g,b,a 	
	glfwSwapInterval( 1 ); ///cap FPS

	currentDC = wglGetCurrentDC();
	currentContext = wglGetCurrentContext();

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

	while ( !glfwWindowShouldClose( window ) )
	{
		///We are about to get keyboard input and other events
		///Polling for input events is the most important function of the engine so Polling is done here in the main thread.
		glfwPollEvents();
	}
	Quit();
	///Makes this thread the current context in which OpenGL rendering can occur
	wglMakeCurrent( currentDC, currentContext );
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
		glfwSetWindowShouldClose( window, GL_TRUE );
	}
}

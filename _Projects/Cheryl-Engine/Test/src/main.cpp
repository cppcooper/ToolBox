///this code sets up memory leak detection
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
#include <stdlib.h>


#include <GF/GameFramework.h>

void main(int argc, char *argv[])
{
	///the line below turns on memory leak detection in debug mode
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 1 );
	Game::Instance().Init();
}

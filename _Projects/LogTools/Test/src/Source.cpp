#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>

#if _MSC_VER >= 1300
#include <Tlhelp32.h>
#endif

#include <tools_logger.h>
using namespace logger;

void func1()
{
	LOGFILE( 0, _DEBUG1 ) << lastcall;
	LOGFILE( 0, _DEBUG1 ) << thiscall;
	for ( int i = 0; i < 1000; ++i )
	{
		LOGFILE( 0, _DEBUG1 ) << "fuck yea! Alright, count is at: " << i;
	}
}

void func2()
{
	LOGFILE_1( _INFO ) << callstack;
	for ( int i = 0; i < 1000; ++i )
	{
		LOGFILE_1( _INFO ) << "fuck yea! Alright, count is at: " << i++;
	}
}

int main()
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 272 );

	LogFile_Manager::RegisterLog( "file1.log", false );

	std::thread t1 = std::thread( func1 );
	std::thread t2 = std::thread( func2 );

	t1.join();
	t2.join();

	InsertStackTrace( std::cout );

	return 0;
}

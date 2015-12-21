#include <tools_logger.h>
using namespace dbg_log;

void func1()
{
	for ( int i = 0; i < 1000; ++i )
	{
		LOGFILEX( 0, DEBUG1 ) << "fuck yea! Alright, count is at: " << i;
	}
}

void func2()
{
	for ( int i = 0; i < 1000; ++i )
	{
		LOGFILE1( DEBUG1 ) << "fuck yea! Alright, count is at: " << i++;
	}
}

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 272 );
	FileLog_Mgr::RegisterNewLog( "file1.log" , true );
	FileLog_Mgr::Start();
	
	std::thread t1 = std::thread( func1 );
	std::thread t2 = std::thread( func2 );

	t1.join();
	t2.join();

	FileLog_Mgr::CloseLogs();

    return -1;
}

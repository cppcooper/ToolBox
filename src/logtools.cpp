#include "../logtools.h"

using namespace dbg_log;

int FileLog_Mgr::StartDelay = 1500;
int FileLog_Mgr::WriteInterval = 2000;
bool FileLog_Mgr::ThreadRunning = false;
std::thread FileLog_Mgr::WtL_Thread;

inline std::string NowTime()
{
	static std::mutex time_mutex;
	time_mutex.lock();
	static std::string date_time;
	static time_t last_raw_time = 0;
	time_t raw_time = std::chrono::high_resolution_clock::to_time_t( std::chrono::high_resolution_clock::now() );

	if ( raw_time != last_raw_time )
	{
		last_raw_time = raw_time;
		tm the_time;
		localtime_s( &the_time, &raw_time );

		char buffer[256];
		strftime( buffer, sizeof( buffer ), "%Y-%m-%d :: %H:%M:%S", &the_time );
		date_time = std::string( buffer );
	}

	static std::string ms;
	static unsigned long long last_epoch_time = 0;
	unsigned long long epoch_time = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::high_resolution_clock::now().time_since_epoch() ).count();

	if ( epoch_time != last_epoch_time )
	{
		last_epoch_time = epoch_time;
		ms = std::to_string( epoch_time % 1000 );
	}
	time_mutex.unlock();
	return ( date_time + '.' + ms );
}

std::vector<FileLog*>& FileLog_Mgr::getLogs()
{
	static std::vector<FileLog*> Logs;
	return Logs;
}

int FileLog_Mgr::RegisterNewLog( std::string file_name, bool thread_safe, bool append, LogLevel reportLevel )
{
	static std::mutex registration_mutex;
	registration_mutex.lock();

	bool original_state = ThreadRunning;
	if ( ThreadRunning )
	{
		Stop();
	}

	for ( unsigned int i = 0; i < getLogs().size(); ++i )
	{
		if ( getLogs()[i]->Output->get_FileName() == file_name )
			return -2;
	}

	FileLog* newLog = new FileLog();
	newLog->ReportingLevel() = reportLevel;
	newLog->Output->set_append( append );
	newLog->Output->set_FileName( file_name );
	newLog->automate_mutex = thread_safe;
	getLogs().push_back( newLog );
	unsigned int index = getLogs().size() - 1;

	if ( original_state )
	{
		Start();
	}

	registration_mutex.unlock();
	return index;
}
FileLog FileLog_Mgr::Get( unsigned int index, LogLevel level )
{
	auto log = getLogs()[index];
	return FileLog( log, level );
}

bool FileLog_Mgr::isThreadSafe( unsigned int index )
{
	return getLogs()[index]->isThreadSafe();
}
bool FileLog_Mgr::CheckIndex( unsigned int index )
{
	if ( index >= 0 && index < getLogs().size() )
		return true;
	return false;
}
bool FileLog_Mgr::macroCheck( unsigned int index, LogLevel level )
{
	if ( CheckIndex( index ) )
	{
		if ( level > getLogs()[index]->ReportingLevel() )
			return false;
		return true;
	}
	return false;
}

void FileLog_Mgr::WriteToLogs()
{
	while ( ThreadRunning )
	{
		for ( auto iter = getLogs().begin(); iter != getLogs().end(); ++iter )
		{
			auto log = *iter;
			log->Lock();
			log->Output->Stream() << log->str();
			log->flush();
			log->str( "" );
			log->Output->Stream().flush();
			log->Unlock();
		}
		std::this_thread::sleep_for( std::chrono::milliseconds( WriteInterval ) );
	}

	//There might be buffered data
	for ( auto iter = getLogs().begin(); iter != getLogs().end(); ++iter )
	{
		auto log = *iter;
		log->Lock();
		log->Output->Stream() << log->str();
		log->flush();
		log->str( "" );
		log->Output->Stream().flush();
		log->Unlock();
	}
}
bool FileLog_Mgr::Start()
{
	if ( WtL_Thread.joinable() )
		return false;

	ThreadRunning = true;
	WtL_Thread = std::thread( &FileLog_Mgr::WriteToLogs );
	std::this_thread::sleep_for( std::chrono::milliseconds( StartDelay ) );
	return true;
}
bool FileLog_Mgr::Stop()
{
	if ( WtL_Thread.joinable() )
	{
		ThreadRunning = false;
		WtL_Thread.join();
		return true;
	}
	return false;
}
void FileLog_Mgr::CloseLogs()
{
	Stop();
	for ( auto iter = getLogs().begin(); iter != getLogs().end(); ++iter )
	{
		auto log = *iter;
		log->Output->Stream().close();
		delete log;
	}
}
void FileLog_Mgr::Lock( unsigned int index )
{
	getLogs()[index]->Lock();
}
void FileLog_Mgr::Unlock( unsigned int index )
{
	getLogs()[index]->Unlock();
}
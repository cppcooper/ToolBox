#include "../tools_logger.h"
#include <cassert>

using namespace logger;

namespace logger
{

	inline std::string GetTimeNow()
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

	inline std::string GetLogLevel( LogLevel level )
	{
		switch ( level )
		{
			case FATAL:
				return "\t~FATAL~\t\t";
				break;

			case ERROR:
				return "\tERROR: \t\t";
				break;

			case WARNING:
				return "WARNING: \t";
				break;

			case INFO:
				return "INFO:\t  ";
				break;

			case DEBUG1:
				return "DEBUG1:\t\t";
				break;

			case DEBUG2:
				return "DEBUG2:\t\t  ";
				break;

			case DEBUG3:
				return "DEBUG3:\t\t    ";
				break;

			case DEBUG4:
				return "DEBUG4:\t\t      ";
				break;

			default:
				return "DoneFucked:\t\t      ";
		}
	}
}


LogStream::LogStream( Policy* OutputPolicy )
{
	m_OutputPolicy = OutputPolicy;
}

LogStream::~LogStream()
{
	if ( m_OutputPolicy )
	{
		m_OutputPolicy->lout( this->str() );
	}
}

#pragma region "Log"

Log::Log( Policy* OutputPolicy )
{
	assert( OutputPolicy );
	m_Policy = OutputPolicy;
}

Log::~Log()
{
	delete m_Policy;
}

LogLevel& Log::ReportingLevel()
{
	static LogLevel level;
	return level;
}

LogStream Log::Get( LogLevel level )
{
	LogStream logStream( m_Policy );
	logStream << std::endl << " -  " << GetTimeNow() << " - \t" << GetLogLevel( level );
	return logStream;
}

#pragma endregion


#pragma region "FilePolicy"

bool FilePolicy::Open( std::string FileName, bool Append )
{
	m_FileLock.lock();
	assert( !m_File.is_open() && m_LogFiles.emplace( FileName ).second );
	m_File.open( FileName, Append ? std::fstream::in | std::fstream::app : std::fstream::in );
	bool bOpen = m_File.is_open();
	m_FileLock.unlock();
	return bOpen;
}

bool FilePolicy::Close()
{
	m_FileLock.lock();
	m_File.close();
	bool bClosed = !m_File.is_open();
	m_FileLock.unlock();
	return bClosed;
}

void FilePolicy::lout( const std::string& LogLine )
{
	m_FileLock.lock();
	assert( m_File.is_open() );
	m_File << LogLine;
	m_FileLock.unlock();
}

#pragma endregion


#pragma region "LogFile_Manager"

LogFile_Manager::~LogFile_Manager()
{
	for ( unsigned int i = 0; i < m_Logs.size(); ++i )
	{
		m_Files[i]->Close();
		delete m_Logs[i];
	}
}

LogFile_Manager& LogFile_Manager::Instance()
{
	static LogFile_Manager instance;
	return instance;
}

unsigned int LogFile_Manager::RegisterLog( std::string FileName, bool Append, LogLevel ReportLevel = DEBUG1 )
{
	FilePolicy* file = new FilePolicy();
	assert( file->Open( FileName, Append ) );
	Log* log = new Log( file );
	log->ReportingLevel() = ReportLevel;
	Instance().m_Files.push_back( file );
	Instance().m_Logs.push_back( log );
}

LogStream LogFile_Manager::Get( unsigned int index, LogLevel level )
{
	if ( index < Instance().m_Logs.size() )
	{
		if ( level <= Instance().m_Logs[index]->ReportingLevel() )
		{
			return Instance().m_Logs[index]->Get( level );
		}
	}
	return LogStream( nullptr );
}

#pragma endregion
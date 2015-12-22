#ifndef _TOOLS_LOGGER_H
#define _TOOLS_LOGGER_H

#ifndef LOG_WRITE_LEVELS
#define LOG_WRITE_LEVELS (logger::FATAL + logger::ERROR + logger::WARNING + logger::INFO + logger::DEBUG1 + logger::DEBUG2 + logger::DEBUG3 + logger::DEBUG4 )
#endif
#pragma comment (lib,"tools_logger.lib")

#include <string>
#include <sstream>
#include <fstream>
#include <mutex>
#include <set>
#include <vector>
#include <thread>
#include <chrono>

namespace logger
{
	//Enums representing the different log levels
	// Implemented as bits in a Byte as to facilitate turning specific levels on and off with a #define macro
	enum LogLevel
	{
		FATAL = 1 << 0, ERROR = 1 << 1,
		WARNING = 1 << 2, INFO = 1 << 3,
		DEBUG1 = 1 << 4, DEBUG2 = 1 << 5,
		DEBUG3 = 1 << 6, DEBUG4 = 1 << 7
	};

	//class Policy: Ouput Policies' Base Class
	class Policy
	{
	public:
		virtual void lout( const std::string& LogLine ) = 0;
	};

	//class LogStream: Core writing mechanic of the Log<T> template class
	class LogStream : public std::stringstream
	{
	private:
		Policy* m_OutputPolicy = nullptr;
	public:
		LogStream( Policy* OutputPolicy );
		~LogStream();
	};

	//class Log: Represents an individual Log... the log's output destination is provided to the log
	class Log
	{
	private:
		Policy* m_Policy = nullptr;
	public:
		Log( Policy* OutputPolicy );
		~Log();
		LogLevel& ReportingLevel();
		LogStream Get( LogLevel level );
	};

	//class FilePolicy: defines how to write logs to a file
	class FilePolicy : public Policy
	{
	private:
		static std::set<std::string> m_LogFiles;
		std::string m_FileName;
		std::mutex m_FileLock;
		std::fstream m_File;
	public:
		bool Open( std::string FileName, bool Append );
		bool Close();
		void lout( const std::string& LogLine ) final override;
	};

	//class LogFile_Manager: manages log files
	class LogFile_Manager
	{
	private:
		std::vector<FilePolicy*> m_Files;
		std::vector<Log*> m_Logs;
		LogFile_Manager(){}
		~LogFile_Manager();
	public:
		static LogFile_Manager& Instance();
		static unsigned int RegisterLog( std::string FileName, bool Append, LogLevel ReportLevel = DEBUG1 );
		static LogStream Get( unsigned int LogIndex, LogLevel level );
	};
}

#define LOGFILE( index, level )		if ( level & ~LOG_WRITE_LEVELS ); else logger::LogFile_Manager::Get( index, level )
#define LOGFILE_1( level )				LOGFILE( 0, level )
#define LOGFILE_2( level )				LOGFILE( 1, level )
#define LOGFILE_3( level )				LOGFILE( 2, level )
#define LOGFILE_4( level )				LOGFILE( 3, level )
#define LOGFILE_5( level )				LOGFILE( 4, level )

#endif

#ifndef _TOOLS_LOGGER_H
#define _TOOLS_LOGGER_H
#pragma once

#ifdef _DEBUG
#pragma comment (lib,"tools_logger_Debug.lib")

#ifndef LOG_WRITE_LEVELS
#define LOG_WRITE_LEVELS (logger::_FATAL + logger::_ERROR + logger::_WARNING + logger::_INFO + logger::_DEBUG1 + logger::_DEBUG2 + logger::_DEBUG3 + logger::_DEBUG4 )
#endif

#else
#pragma comment (lib,"tools_logger_Release.lib")

#ifndef LOG_WRITE_LEVELS
#define LOG_WRITE_LEVELS \
(logger::_FATAL + logger::_ERROR + logger::_WARNING )

#endif

#endif

#include "stacktracer.h"

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
		_FATAL = 1 << 0, _ERROR = 1 << 1,
		_WARNING = 1 << 2, _INFO = 1 << 3,
		_DEBUG1 = 1 << 4, _DEBUG2 = 1 << 5,
		_DEBUG3 = 1 << 6, _DEBUG4 = 1 << 7
	};


	//class Policy: Ouput Policies' Base Class
	class Policy
	{
	public:
		virtual bool Close() = 0;
		virtual void lout( const std::string& LogLine ) = 0;
	};

	//class LogStream: Core writing mechanic of the Log<T> template class
	class LogStream : public std::stringstream
	{
	private:
		Policy* m_OutputPolicy = nullptr;
		bool m_CallInfo = false;
	public:
		LogStream( Policy* OutputPolicy );
		LogStream( LogStream& obj );
		~LogStream();
		void ShowCallStackTop();
	};

	//class Log: Represents an individual Log... the log's output destination is provided to the log
	class Log
	{
	private:
		Policy* m_Policy = nullptr;
	public:
		Log( Policy* OutputPolicy );
		LogLevel& ReportingLevel();
		LogStream Line( LogLevel level );
	};

	//class FilePolicy: defines how to write logs to a file
	class FilePolicy : public Policy
	{
	private:
		static std::set<std::string> m_LogFiles;
		std::string m_FileName;
		std::mutex m_FileLock;
		std::ofstream m_File;
	public:
		~FilePolicy();
		bool Open( std::string FileName, bool Append );
		bool Close() final override;
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
		static unsigned int RegisterLog( std::string FileName, bool Append, LogLevel ReportLevel = _DEBUG1 );
		static LogStream Get( unsigned int LogIndex, LogLevel level );
		static Log& GetLog( unsigned int LogIndex );
	};

	template< class CharT, class Traits >
	std::basic_ostream<CharT, Traits>& newl( std::basic_ostream<CharT, Traits>& os )
	{
		os << std::endl << "\t\t\t\t\t   ";
		return os;
	}

	template< class CharT, class Traits >
	std::basic_ostream<CharT, Traits>& lastcall( std::basic_ostream<CharT, Traits>& os )
	{
		InsertStackTrace( os, 5, 1 );
		return os;
	}

	template< class CharT, class Traits >
	std::basic_ostream<CharT, Traits>& thiscall( std::basic_ostream<CharT, Traits>& os )
	{
		InsertStackTrace( os, 4, 1 );
		return os;
	}

	template< class CharT, class Traits >
	std::basic_ostream<CharT, Traits>& callstack( std::basic_ostream<CharT, Traits>& os )
	{
		InsertStackTrace( os, 4 );
		return os;
	}
}

#define LOGFILE( index, level )		if ( level & ~LOG_WRITE_LEVELS ); else logger::LogFile_Manager::Get( index, level )
#define LOGFILE_1( level )				LOGFILE( 0, level )
#define LOGFILE_2( level )				LOGFILE( 1, level )
#define LOGFILE_3( level )				LOGFILE( 2, level )
#define LOGFILE_4( level )				LOGFILE( 3, level )
#define LOGFILE_5( level )				LOGFILE( 4, level )
#endif

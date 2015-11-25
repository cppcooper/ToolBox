#ifndef _DBG_LOG_
#define _DBG_LOG_

#ifndef LOG_MAX_LEVEL
#define LOG_MAX_LEVEL (dbg_log::logFATAL + dbg_log::logERROR + dbg_log::logWARNING + dbg_log::logINFO + dbg_log::logDEBUG1 + dbg_log::logDEBUG2 + dbg_log::logDEBUG3 + dbg_log::logDEBUG4 )
#endif
#pragma comment (lib,"logtools.lib")

#include <vector>
#include <fstream>
#include <sstream>
#include <mutex>
#include <thread>

#include <chrono>
#include <string>

extern inline std::string NowTime();


namespace dbg_log
{
	//Enums representing the different log levels
	// Implemented as bits in a Byte as to facilitate turning specific levels on and off with a #define macro
	enum LogLevel
	{
		logFATAL = 1 << 0, logERROR = 1 << 1,
		logWARNING = 1 << 2, logINFO = 1 << 3,
		logDEBUG1 = 1 << 4, logDEBUG2 = 1 << 5,
		logDEBUG3 = 1 << 6, logDEBUG4 = 1 << 7
	};

	//Forward declaration for friend statement
	class FileLog_Mgr;

	/*
	Logger Class

	
	*/
	template <typename OutputPolicy>
	class Logger : public std::ostringstream
	{
		friend FileLog_Mgr;

	public:
		virtual ~Logger()
		{
			if ( original_object )
			{
				( *original_object ) << str();
				if ( isThreadSafe() )
					Unlock();
			}
			else
			{
				delete Log_mutex;
				delete Output;
			}
		}
		Logger()
		{
			original_object = nullptr;
			Log_mutex = new std::mutex();
			Output = new OutputPolicy();
		}
		Logger( const Logger& obj ) = delete;
		Logger( Logger* other, LogLevel level )
		{
			original_object = other;
			automate_mutex = other->automate_mutex;
			Log_mutex = other->Log_mutex;
			//ReportingLevel() = other.ReportingLevel();
			if ( isThreadSafe() )
				Lock();
			NewLogLine( level );
		}

		inline LogLevel& ReportingLevel()
		{
			static LogLevel reportingLevel = logDEBUG4;
			return reportingLevel;
		}
		inline std::string ToString( LogLevel level )
		{
			switch ( level )
			{
				case logFATAL:
					return "\t~FATAL~\t\t";
					break;

				case logERROR:
					return "\tERROR: \t\t";
					break;

				case logWARNING:
					return "WARNING: \t";
					break;

				case logINFO:
					return "INFO:\t  ";
					break;

				case logDEBUG1:
					return "DEBUG1:\t\t";
					break;

				case logDEBUG2:
					return "DEBUG2:\t\t  ";
					break;

				case logDEBUG3:
					return "DEBUG3:\t\t    ";
					break;

				case logDEBUG4:
					return "DEBUG4:\t\t      ";
					break;

				default:
					return "DoneFucked:\t\t      ";
			}
		}
		inline void NewLogLine( LogLevel level = logINFO )
		{
			*this << std::endl << " -  " << NowTime() << " - \t";
			*this << ToString( level );
		}

		inline bool isThreadSafe() const { return automate_mutex; }
		inline void Lock()
		{
			Log_mutex->lock();
		}
		inline void Unlock()
		{
			Log_mutex->unlock();
		}

	protected:
		std::mutex* Log_mutex = nullptr;
		OutputPolicy* Output = nullptr;  //templated output

	private:
		bool automate_mutex = false;
		Logger* original_object = nullptr;
	};

	class FileStream_Policy
	{
	public:
		FileStream_Policy(){}

		inline std::ofstream& Stream()
		{
			if ( !file_stream.is_open() )
			{
				if ( app )
				{
					file_stream.open( file_name, std::ofstream::out | std::ofstream::app );
				}
				else
				{
					file_stream.open( file_name, std::ofstream::out );
				}
			}
			return file_stream;
		}
		inline const std::string& get_FileName()
		{
			return file_name;
		}
		void set_FileName( std::string& file_name )
		{
			this->file_name = file_name;
		}
		inline void set_append( bool append )
		{
			app = append;
		}

	protected:
		bool app = false;
		std::ofstream file_stream;
		std::string file_name;
	};

	//Type Definition for a File Log using Logger<FileStream_Policy>
	using FileLog = Logger < FileStream_Policy > ;

	class FileLog_Mgr
	{
	private:
		static bool ThreadRunning;
		static std::thread WtL_Thread;

	protected:
		static std::vector<FileLog*>& getLogs();
		static void WriteToLogs();

	public:
		static int WriteInterval;
		static int StartDelay;

		static int RegisterNewLog( std::string file_name, bool thread_safe = false, bool append = false, LogLevel reportLevel = logDEBUG1 );
		static FileLog Get( unsigned int index, LogLevel level );

		static bool isThreadSafe( unsigned int index );
		static bool CheckIndex( unsigned int index );
		static bool macroCheck( unsigned int index, LogLevel level );
		
		static bool Start();
		static bool Stop();
		static void CloseLogs();
		static void Lock( unsigned int index );
		static void Unlock( unsigned int index );



	};
}

#define LOGFILEX_LOCK( index ) \
	if ( !dbg_log::FileLog_Mgr::macroCheck( index, level ) ); \
		else dbg_log::FileLog_Mgr::Lock( index )

#define LOGFILEX_UNLOCK( index, level ) \
	if ( !dbg_log::FileLog_Mgr::macroCheck( index, level ) ); \) \
		else dbg_log::FileLog_Mgr::Unlock( index )

#define LOGFILEX( index, level ) \
	if ( level & ~LOG_MAX_LEVEL || !dbg_log::FileLog_Mgr::macroCheck( index, level ) ); \
		else dbg_log::FileLog_Mgr::Get( index, level )

#define LOGFILE1(level) \
	if ( level & ~LOG_MAX_LEVEL || !dbg_log::FileLog_Mgr::macroCheck(0, level) ); \
		else dbg_log::FileLog_Mgr::Get(0, level)

#define LOGFILE2(level) \
	if ( level & ~LOG_MAX_LEVEL || !dbg_log::FileLog_Mgr::macroCheck(1, level) ); \
		else dbg_log::FileLog_Mgr::Get( 1, level )

#define LOGFILE3(level) \
	if ( level & ~LOG_MAX_LEVEL || !dbg_log::FileLog_Mgr::macroCheck(2, level) ); \
		else dbg_log::FileLog_Mgr::Get( 2, level )

#define LOGFILE4(level) \
	if ( level & ~LOG_MAX_LEVEL || !dbg_log::FileLog_Mgr::macroCheck(3, level) ); \
		else dbg_log::FileLog_Mgr::Get( 3, level )

#define LOGFILE5(level) \
	if ( level & ~LOG_MAX_LEVEL || !dbg_log::FileLog_Mgr::macroCheck(4, level) ); \
		else dbg_log::FileLog_Mgr::Get( 4, level )

#endif
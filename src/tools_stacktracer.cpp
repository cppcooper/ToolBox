/* This function, in its original form, was found in the comment section of an msdn article
The article was the CaptureStackBackTrace function
found: https://msdn.microsoft.com/en-us/library/windows/desktop/bb204633(v=vs.85).aspx
Which was in turn based on a StackOverflow answer

Well mine is based on that comment, because I have changed very little outside of formatting.
*/
#define _TOOLS_SKIPLIB
#include "../tools_stacktracer.h"
//#include "../stacktracer.h"
#include <mutex>
#include <string>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <WinBase.h>
#include <fstream>
#include "DbgHelp.h"
#pragma comment(lib, "Dbghelp.lib")

StackTracer& StackTracer::Instance()
{
	static StackTracer instance;
	return instance;
}

void StackTracer::InsertStackTrace( std::ostream& os, __int8 skip, unsigned __int8 capture )
{
	// Quote from Microsoft Documentation:
	// ## Windows Server 2003 and Windows XP:  
	// ## The sum of the FramesToSkip and FramesToCapture parameters must be less than 63.
	const int kMaxCallers = 62;

	Instance().m_Lock.lock();
	capture = capture > 62 ? 62 : capture;
	typedef USHORT( WINAPI *CaptureStackBackTraceType )( __in ULONG, __in ULONG, __out PVOID*, __out_opt PULONG );
	
	CaptureStackBackTraceType func = (CaptureStackBackTraceType)( GetProcAddress( LoadLibrary( "kernel32.dll" ), "RtlCaptureStackBackTrace" ) );
	if ( func == NULL )
	{
		Instance().m_Lock.unlock();
		return; // WOE 29.SEP.2010
	}

	SYMBOL_INFO* symbol = (SYMBOL_INFO *)calloc( sizeof( SYMBOL_INFO ) + 256 * sizeof( char ), 1 );
	symbol->MaxNameLen = 255;
	symbol->SizeOfStruct = sizeof( SYMBOL_INFO );

	HANDLE process = GetCurrentProcess();
	SymInitialize( process, NULL, TRUE );
	void* callers_stack[kMaxCallers];
	unsigned short frames = (func)( 0, kMaxCallers, callers_stack, NULL );

	frames = frames < ( capture + skip ) ? frames : ( capture + skip );
	os << std::endl << "\tThread ID: " << GetCurrentThreadId() << std::endl;
	for ( unsigned int i = skip; i < frames; i++ )
	{
		SymFromAddr( process, (DWORD64)( callers_stack[i] ), 0, symbol );
		os << "\t\tFrame: " << i - skip 
			<< ",\t0x" << callers_stack[i] 
			<< " _Symbol:\t0x" << (void*)symbol->Address 
			<< ", " << symbol->Name 
			<< std::endl;
	}

	free( symbol );
	Instance().m_Lock.unlock();
}

void InsertStackTrace( std::ostream& os, __int8 skip, unsigned __int8 capture )
{
	StackTracer::InsertStackTrace( os, skip, capture );
}


extern "C"
{
	__declspec(dllexport) void __cdecl LogStackTrace()
	{
		int skip = 0;
		int capture = 62;
		// Quote from Microsoft Documentation:
		// ## Windows Server 2003 and Windows XP:  
		// ## The sum of the FramesToSkip and FramesToCapture parameters must be less than 63.
		const int kMaxCallers = 62;

		capture = capture > 62 ? 62 : capture;
		typedef USHORT( WINAPI *CaptureStackBackTraceType )(__in ULONG, __in ULONG, __out PVOID*, __out_opt PULONG);

		CaptureStackBackTraceType func = (CaptureStackBackTraceType)(GetProcAddress( LoadLibrary( "kernel32.dll" ), "RtlCaptureStackBackTrace" ));
		if ( func == NULL )
		{
			return; // WOE 29.SEP.2010
		}

		SYMBOL_INFO* symbol = (SYMBOL_INFO *)calloc( sizeof( SYMBOL_INFO ) + 256 * sizeof( char ), 1 );
		symbol->MaxNameLen = 255;
		symbol->SizeOfStruct = sizeof( SYMBOL_INFO );

		HANDLE process = GetCurrentProcess();
		SymInitialize( process, NULL, TRUE );
		void* callers_stack[kMaxCallers];
		unsigned short frames = (func)(0, kMaxCallers, callers_stack, NULL);

		frames = frames < (capture + skip) ? frames : (capture + skip);
		std::stringstream os;
		os << std::endl << "\tThread ID: " << GetCurrentThreadId() << std::endl;
		for ( unsigned int i = skip; i < frames; i++ )
		{
			SymFromAddr( process, (DWORD64)(callers_stack[i]), 0, symbol );
			os << "\t\tFrame: " << i - skip
				<< ",\t0x" << callers_stack[i]
				<< " _Symbol:\t0x" << (void*)symbol->Address
				<< ", " << symbol->Name
				<< std::endl;
		}
		free( symbol );

		std::ofstream File;
		File.open( "stacktrace.log", std::ios_base::out | std::ios_base::app | std::ios_base::ate );
		if ( File.is_open() )
		{
			File << std::endl << os.str() << std::endl;
			File.close();
		}
	}
}
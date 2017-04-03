/* This function, in its original form, was found in the comment section of an msdn article
The article was the CaptureStackBackTrace function
found: https://msdn.microsoft.com/en-us/library/windows/desktop/bb204633(v=vs.85).aspx
Which was in turn based on a StackOverflow answer

Well mine is based on that comment, because I have changed very little outside of formatting.
*/
#ifndef _TOOLS_STACKTRACER_H
#define _TOOLS_STACKTRACER_H

#ifndef _TOOLS_SKIPLIB
#ifdef _TOOLS_LIB64

#ifdef _DEBUG
#pragma comment (lib,"x64\\tools_stacktracer_Debug.lib")
#else
#pragma comment (lib,"x64\\tools_stacktracer_Release.lib")
#endif

#else //_TOOLS_LIB86

#ifdef _DEBUG
#pragma comment (lib,"Win32\\tools_stacktracer_Debug.lib")
#else
#pragma comment (lib,"Win32\\tools_stacktracer_Release.lib")
#endif

#endif
#endif

#include <ostream>
#include <mutex>
class StackTracer
{
	std::mutex m_Lock;
	StackTracer() {}
public:
	static StackTracer& Instance();
	static void InsertStackTrace( std::ostream& os, __int8 skip = 0, unsigned __int8 capture = 62 );
};
extern void InsertStackTrace( std::ostream& os, __int8 skip = 0, unsigned __int8 capture = 62 );

extern "C" {
	__declspec(dllexport) void __cdecl LogStackTrace();
}


#endif
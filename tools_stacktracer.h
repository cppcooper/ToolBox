/* This function, in its original form, was found in the comment section of an msdn article
The article was the CaptureStackBackTrace function
found: https://msdn.microsoft.com/en-us/library/windows/desktop/bb204633(v=vs.85).aspx
Which was in turn based on a StackOverflow answer

Well mine is based on that comment, because I have changed very little outside of formatting.
*/
#ifndef _TOOLS_STACKTRACER_H
#define _TOOLS_STACKTRACER_H

#include <ostream>
#include <mutex>
class StackTracer
{
	std::mutex m_Lock;
	StackTracer(){}
public:
	static StackTracer& Instance();
	static void InsertStackTrace( std::ostream& os, __int8 skip = 0, unsigned __int8 capture = 62 );
};
extern void InsertStackTrace( std::ostream& os, __int8 skip = 0, unsigned __int8 capture = 62 );

#endif
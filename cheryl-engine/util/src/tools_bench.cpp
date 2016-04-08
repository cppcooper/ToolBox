#include "../tools_bench.h"

time_lord bench;

void time_lord::set_TimePoint_A()
{
	Point_A = my_clock.now();
	seconds = ( Point_B > Point_A ) ? ( Point_B - Point_A ) : ( Point_A - Point_B );
}
void time_lord::set_TimePoint_B()
{
	Point_B = my_clock.now();
	seconds = ( Point_B > Point_A ) ? ( Point_B - Point_A ) : ( Point_A - Point_B );
}

double time_lord::Elapsed_seconds()
{
	return seconds.count();
}
long long time_lord::Elapsed_milliseconds()
{
	ms = duration_cast<milliseconds>( seconds );
	return ms.count();
}
std::string time_lord::Elapsed_quickstamp()
{
	return "HH:MM:SS:MS";
}
std::string time_lord::Elapsed_timestamp()
{
	return "YYYY.MM.DD - HH:MM:SS:MS";
}
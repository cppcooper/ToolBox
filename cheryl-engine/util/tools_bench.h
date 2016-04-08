#ifndef BENCH_H
#define BENCH_H

#include <string>
#include <chrono>

#ifdef _DEBUG
#pragma comment (lib,"tools_bench_Debug.lib")
#else
#pragma comment (lib,"tools_bench_Release.lib")
#endif

using namespace std::chrono;

namespace bench_h
{
	typedef std::chrono::time_point<system_clock> TimePoint;
}
class time_lord
{
private:
	system_clock my_clock;
	bench_h::TimePoint Point_A;
	bench_h::TimePoint Point_B;
	time_t elapsed;

	milliseconds ms;
	duration<double> seconds;

public:
	void set_TimePoint_A();
	void set_TimePoint_B();
	
	double Elapsed_seconds();
	long long Elapsed_milliseconds();
	std::string Elapsed_quickstamp();
	std::string Elapsed_timestamp();
};

extern time_lord bench;

#endif
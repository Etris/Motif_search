#include <chrono>
#pragma once
class timer
{
	std::chrono::time_point<std::chrono::system_clock> s, e;
	std::chrono::duration<double> elapsed_seconds;
public:
	void start();
	double end();
	double getLastTime();
};


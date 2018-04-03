#include "timer.h"
void timer::start() {
	elapsed_seconds = std::chrono::duration<double>::zero();
	s = std::chrono::system_clock::now();
}

double timer::end() {
	e = std::chrono::system_clock::now();
	elapsed_seconds = e - s;
	return elapsed_seconds.count();
}

double timer::getLastTime() {
	return elapsed_seconds.count();
}

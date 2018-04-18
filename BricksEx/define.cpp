#include "define.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iomanip>

float MAINPLAYERSPEED = 6.f;
const size_t startTimeP = static_cast<size_t>(std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::steady_clock::now()).time_since_epoch().count());

namespace GameState {
	bool start = false;
	bool ready = false;
	bool light = false;
	bool finishLevel = false;
	bool pause = false;
	bool lock = false;
};

const int rng(const int lowerLimit, const int upperLimit) {
	static thread_local std::mt19937 generator(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
	const std::uniform_int_distribution<> dist(lowerLimit, upperLimit);
	return static_cast<int>(dist(generator));
}

const int prng(const int lowerLimit) {
	return rng(lowerLimit);
}

void getPlayedTime() {
	const size_t endTimeP = static_cast<size_t>(std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::steady_clock::now()).time_since_epoch().count());
	const size_t playedTime = endTimeP - startTimeP;
	const size_t sec = playedTime >= 60 ? playedTime % 60 : playedTime;
	const size_t min = playedTime >= 3600 ? playedTime / 3600 : playedTime / 60;
	const size_t hr = playedTime >= 86400 ? playedTime / 86400 : playedTime / 3600;
	const size_t day = playedTime / 86400;
	std::cout
		<< day << ":"
		<< std::setw(2) << std::setfill('0') << hr << ":" 
		<< std::setw(2) << std::setfill('0') << min << ":" 
		<< std::setw(2) << std::setfill('0') << sec << std::endl;
}

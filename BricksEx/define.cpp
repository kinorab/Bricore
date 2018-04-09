#include "define.h"
#include <chrono>
#include <random>
#include <algorithm>

unsigned int level = 5;
float MAINPLAYERSPEED = 6.f;

namespace GameState {
	bool start = false;
	bool ready = false;
	bool light = false;
	bool finishLevel = false;
	bool pause = false;
	bool lock = false;
};

int rng() {
	return rng(std::numeric_limits<int>().min(), std::numeric_limits<int>().max());
}

int rng(int lowerLimit, int upperLimit) {
	static thread_local std::mt19937 generator(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<> dist(lowerLimit, upperLimit);
	return static_cast<int>(dist(generator));
}

int prng(const int lowerLimit) {
	return rng(lowerLimit, std::numeric_limits<int>().max());
}
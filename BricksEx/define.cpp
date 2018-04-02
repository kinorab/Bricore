#include "define.h"
#include <chrono>
#include <random>
#include <algorithm>

unsigned int level = 1;
float MAINPLAYERSPEED = 5.5f;

namespace GameState {
	bool start = false;
	bool ready = false;
	bool light = false;
	bool finishLevel = false;
	bool pause = false;
	bool lock = false;
};

const int rng() {
	static thread_local std::mt19937 prng(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
	return static_cast<int>(prng());
}

const size_t Prng() {
	const size_t PNum = std::abs(rng());
	if (PNum > 100000) {
		return PNum;
	}
	else {
		return Prng();
	}
}
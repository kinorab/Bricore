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

const int rng() {
	static thread_local std::mt19937 prng(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
	return static_cast<int>(prng());
}

const size_t Prng(const size_t PRange) {
	const size_t PNum = abs(rng());
	if (PNum >= PRange) {
		return PNum;
	}
	else {
		return Prng(PRange);
	}
}
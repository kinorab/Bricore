#include "define.h"
#include <chrono>
#include <random>

unsigned int stage = 1;

namespace GameState {
	bool start = false;
	bool ready = false;
	bool active = false;
	bool light = false;
	bool broke = false;
};

int rng() {
	static thread_local std::mt19937 prng(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
	return static_cast<int>(prng());
}
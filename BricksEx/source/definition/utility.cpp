#include "utility.h"
#include <chrono>
#include <random>

const int rng(const int lowerLimit, const int upperLimit) {
	static thread_local std::mt19937 generator(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
	const std::uniform_int_distribution<> dist(lowerLimit, upperLimit);
	return static_cast<int>(dist(generator));
}

const int prng(const int lowerLimit) {
	return rng(lowerLimit);
}

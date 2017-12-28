#pragma once

#include<chrono>
#include<random>

static int rng() {
	static thread_local std::mt19937 prng(std::chrono::system_clock::now().time_since_epoch().count());
	return static_cast<int>(prng());
}

#define PI 3.141592654f
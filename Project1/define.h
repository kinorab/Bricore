#pragma once

#include<chrono>
#include<random>

#define PI 3.141592654f
#define LIFETIME 1500.f
#define PLAYERSPEED 5.5f
#define RESETTIME 20.f

static int rng() {
	static thread_local std::mt19937 prng(std::chrono::system_clock::now().time_since_epoch().count());
	return static_cast<int>(prng());
}
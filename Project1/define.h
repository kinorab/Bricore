#pragma once

#include <chrono>
#include <random>

static unsigned int stage = 1;

static constexpr float PI = 3.141592654f;
static constexpr float LIFETIME = 1500.f;
static constexpr float PLAYERSPEED = 5.5f;
static constexpr float RESETTIME = 20.f;
static constexpr float BOOST = 2.5f;
static constexpr float MAXSPEED = 13.f;
static constexpr float GAME_WIDTH = 1500.f;
static constexpr float GAME_HEIGHT = 900.f;
static constexpr float STAGE_WIDTH = 1200.f;
static constexpr float STAGE_HEIGHT = 900.f;

// it can define in new file(do this, please remove define.cpp also), or keeping here
// whether change it or not, please delete the comment line
struct GameState{
	static bool start;
	static bool ready;
	static bool active;
	static bool light;
	static bool broke;
};

static int rng() {
	static thread_local std::mt19937 prng(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
	return static_cast<int>(prng());
}
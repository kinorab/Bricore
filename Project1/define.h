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

namespace GameState {
	static bool start = false;
	static bool ready = false;
	static bool active = false;
	static bool light = false;
	static bool broke = false;
};

static int rng() {
	static thread_local std::mt19937 prng(static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
	return static_cast<int>(prng());
}
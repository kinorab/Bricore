#pragma once

#include<chrono>
#include<random>

static constexpr float PI = 3.141592654f;
static constexpr float LIFETIME = 1500.f;
static constexpr float PLAYERSPEED = 5.5f;
static constexpr float RESETTIME = 20.f;
static constexpr float BOOST = 2.5f;
static constexpr int GAME_WIDTH = 1500;
static constexpr int GAME_HEIGHT = 900;
static constexpr int STAGE_WIDTH = 1200;
static constexpr int STAGE_HEIGHT = 900;

static int rng() {
	static thread_local std::mt19937 prng(std::chrono::system_clock::now().time_since_epoch().count());
	return static_cast<int>(prng());
}
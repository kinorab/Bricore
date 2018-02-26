#pragma once

extern unsigned int stage;

constexpr float PI = 3.141592654f;
constexpr float LIFETIME = 1500.f;
constexpr float RESETTIME = 20.f;
constexpr float BOOST = 2.5f;
constexpr float MAXSPEED = 13.f;
constexpr float GAME_WIDTH = 1500.f;
constexpr float GAME_HEIGHT = 900.f;
constexpr float STAGE_WIDTH = 1200.f;
constexpr float STAGE_HEIGHT = 900.f;

namespace GameState {
	extern bool start;
	extern bool ready;
	extern bool active;
	extern bool light;
};

extern const int rng();
#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

extern void getPlayedTime();

constexpr float RESETTIME = 25.f;
constexpr float BOOST = 2.5f;
constexpr float MAXSPEED = 15.f;
constexpr float GAME_WIDTH = 1500.f;
constexpr float GAME_HEIGHT = 900.f;
constexpr float LEVEL_WIDTH = 1200.f;
constexpr float LEVEL_HEIGHT = 900.f;
constexpr float AREAINTERVAL = 50.f;
constexpr size_t SLICE = 5;

enum class GameState {
	LEVEL_FINISHED,
	STARTED,
	READY,
	NOT_READY,
};

namespace game {
	extern GameState currentState;
};

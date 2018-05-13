#pragma once

#include <limits>
#include <SFML/Graphics/RectangleShape.hpp>

extern float MAINPLAYERSPEED;
extern const size_t startTimeP;

constexpr float PI = 3.141592654f;
constexpr float LIFETIME = 1500.f;
constexpr float RESETTIME = 25.f;
constexpr float BOOST = 2.5f;
constexpr float MAXSPEED = 20.f;
constexpr float GAME_WIDTH = 1500.f;
constexpr float GAME_HEIGHT = 900.f;
constexpr float LEVEL_WIDTH = 1200.f;
constexpr float LEVEL_HEIGHT = 900.f;
constexpr float AREAINTERVAL = 50.f;
constexpr size_t SLICE = 5;

namespace GameState {
	extern bool start;
	extern bool ready;
	extern bool light;
	extern bool finishLevel;
	extern bool pause;
	extern bool lock;
	extern sf::RectangleShape bricksArea;
	extern sf::RectangleShape obstacleArea;
	extern sf::RectangleShape playerArea;
};

extern const int rng(const int lowerLimit = std::numeric_limits<int>().min(), const int upperLimit = std::numeric_limits<int>().max());
extern const int prng(const int lowerLimit = 0);
extern void getPlayedTime();

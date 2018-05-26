#include "define.h"
#include <chrono>

float MAINPLAYERSPEED = 6.f;
const size_t startTimeP = static_cast<size_t>(std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::steady_clock::now()).time_since_epoch().count());

namespace GameState {
	bool start = false;
	bool ready = false;
	bool light = false;
	bool finishLevel = false;
	bool pause = false;
	bool lock = false;
	sf::RectangleShape bricksArea;
	sf::RectangleShape obstacleArea;
	sf::RectangleShape playerArea;
};

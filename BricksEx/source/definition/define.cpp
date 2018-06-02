#include "define.h"
#include <chrono>

float MAINPLAYERSPEED = 6.f;

namespace GameState {
	bool start = false;
	bool ready = false;
	bool finishLevel = false;
	bool pause = false;
	bool lock = false;
	sf::RectangleShape bricksArea;
	sf::RectangleShape obstacleArea;
	sf::RectangleShape playerArea;
};

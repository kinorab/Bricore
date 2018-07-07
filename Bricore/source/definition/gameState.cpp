#include "gameState.h"
#include "utility.h"
#include <chrono>
#include <iomanip>

static const size_t startTimeP = static_cast<size_t>(std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::steady_clock::now()).time_since_epoch().count());

void getPlayedTime() {
	const size_t endTimeP = static_cast<size_t>(std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::steady_clock::now()).time_since_epoch().count());
	const size_t playedTime = endTimeP - startTimeP;
	const size_t sec = playedTime >= 60 ? playedTime % 60 : playedTime;
	const size_t min = playedTime >= 3600 ? playedTime / 3600 : playedTime / 60;
	const size_t hr = playedTime >= 86400 ? playedTime / 86400 : playedTime / 3600;
	const size_t day = playedTime / 86400;
	std::cout
		<< day << ":"
		<< std::setw(2) << std::setfill('0') << hr << ":"
		<< std::setw(2) << std::setfill('0') << min << ":"
		<< std::setw(2) << std::setfill('0') << sec << std::endl;
}

namespace game {
	GameState currentState = GameState::NOT_READY;
	sf::RectangleShape wallArea;
	sf::RectangleShape obstacleArea;
	sf::RectangleShape playerArea;
};

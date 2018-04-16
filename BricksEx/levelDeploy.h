#pragma once
#include "matrix.h"
#include "SFML/System/Vector2.hpp"

namespace item {
	class Brick;
}
class Obstacle;

namespace sf {
	class Color;
}

class LVDeploy {
public:
	LVDeploy();
	static void finishLevel();
	static const size_t getLevel();
	// obstacles deployment
	static void changeObstacleD() noexcept;
	// bricks deployment
	static void changeBrickD() noexcept;

private:
	static float blockLength;
	static float incre1;
	static size_t level;
	static const std::vector<sf::Vector2f> getBlockSLD() noexcept;
	static const std::vector<sf::Vector2f> getBlockPD() noexcept;
	static const std::vector<sf::Color> getBlockCD() noexcept;
	static const std::vector<sf::Vector2f> getBlockSD() noexcept;
	static const std::vector<sf::Color> getBrickCD() noexcept;
	static sys::Matrix<sf::Vector2f> blockPositionDeploy;
	static sys::Matrix<sf::Vector2f> blockSideLengthDeploy;
	static sys::Matrix<sf::Color> blockColorDeploy;
	static sys::Matrix<sf::Vector2f> blockSpeedDeploy;
	// temp settings
	static std::vector<item::Brick> brickDeploy;
	static sys::Matrix<sf::Color> brickColorDeploy;
};
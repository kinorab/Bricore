#pragma once

#include "../definition/matrix.h"
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
	static void finishLevel() noexcept;
	// deployment component
	static const std::vector<sf::Vector2f> getBlockSLD() noexcept;
	static const std::vector<sf::Vector2f> getBlockPD() noexcept;
	static const std::vector<sf::Color> getBlockCD() noexcept;
	static const std::vector<sf::Vector2f> getBlockSD() noexcept;
	static const std::vector<sf::Color> getBrickCD() noexcept;
	static const std::vector<float> getBrickD() noexcept;

private:
	static float fBlockLength;
	static float fSpan;
	static size_t uLevel;
	static sys::Matrix<sf::Vector2f> blockPositionDeploy;
	static sys::Matrix<sf::Vector2f> blockSideLengthDeploy;
	static sys::Matrix<sf::Color> blockColorDeploy;
	static sys::Matrix<sf::Vector2f> blockSpeedDeploy;
	// temp settings
	static sys::Matrix<sf::Color> brickColorDeploy;
	static sys::Matrix<float> brickDeploy;
};
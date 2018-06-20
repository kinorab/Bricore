#include "LVDeploy.h"
#include "../stuff/brick.h"
#include "../stuff/ball.h"
#include "../stuff/obstacle.h"
#include "../stuff/player.h"
#include "../definition/gameState.h"
#include "../definition/utility.h"
#include <SFML/Graphics/Color.hpp>

float LVDeploy::blockLength(100.f);
float LVDeploy::incre1(3.f);
size_t LVDeploy::level = 1;
sys::Matrix<sf::Vector2f> LVDeploy::blockPositionDeploy({
	// level 1
	{ sf::Vector2f(blockLength, blockLength * incre1)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.75f)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1 * 1.75f)
	, sf::Vector2f((LEVEL_WIDTH - blockLength) / 2 , (LEVEL_HEIGHT - blockLength * incre1) / 2) }
	// level 2
	, { sf::Vector2f(blockLength, blockLength * incre1)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.75f)}
	// level 3
	,{ sf::Vector2f(blockLength, blockLength * incre1)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.75f)}
	// level 4
	,{ sf::Vector2f(blockLength, blockLength * incre1)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.75f)
	, sf::Vector2f((LEVEL_WIDTH - blockLength) / 2 , (LEVEL_HEIGHT - blockLength * incre1) / 2) }
	// level 5
	,{ sf::Vector2f(blockLength, blockLength * incre1)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.75f)
	, sf::Vector2f(blockLength * 2, blockLength * incre1 * 1.5f) }
	// level 6
	,{ sf::Vector2f(blockLength, blockLength * incre1)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 4, blockLength * incre1)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.75f)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1 * 1.75f)
	, sf::Vector2f((LEVEL_WIDTH - blockLength) / 2 , (LEVEL_HEIGHT - blockLength * incre1) / 2) }
	// level 7
	,{ sf::Vector2f(blockLength, blockLength * incre1)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.75f)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1 * 1.75f)
	, sf::Vector2f((LEVEL_WIDTH - blockLength) / 2 , (LEVEL_HEIGHT - blockLength * incre1) / 2) }
	// level 8
	,{ sf::Vector2f(blockLength, blockLength * incre1)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.75f)
	, sf::Vector2f((LEVEL_WIDTH - blockLength) / 2 , (LEVEL_HEIGHT - blockLength * incre1) / 2) }
	// level 9
	,{ sf::Vector2f(blockLength, blockLength * incre1)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.75f)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1 * 1.75f)
	, sf::Vector2f((LEVEL_WIDTH - blockLength) / 2 , (LEVEL_HEIGHT - blockLength * incre1) / 2) }
	// level 10
	,{ sf::Vector2f(blockLength, blockLength * incre1)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.75f)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1 * 1.75f)
	, sf::Vector2f((LEVEL_WIDTH - blockLength) / 2 , (LEVEL_HEIGHT - blockLength * incre1) / 2) }
	});
sys::Matrix<sf::Vector2f> LVDeploy::blockSideLengthDeploy({
	// level 1
	{ sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.25f) }
	// level 2
	, { sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.2f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.2f) }
	// level 3
	,{ sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.3f) }
	// level 4
	,{ sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.7f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.6f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.25f) }
	// level 5
	,{ sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.4f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.7f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.6f) }
	// level 6
	,{ sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.1f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.3f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.f)
	, sf::Vector2f(blockLength * 2, blockLength * incre1 * 0.5f) }
	// level 7
	,{ sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.6f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.4f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.6f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.f) }
	// level 8
	,{ sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.4f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.6f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.75f)
 }
	// level 9
	,{ sf::Vector2f(blockLength, blockLength * incre1 * 0.23f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.45f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.65f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.7f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.f) }
	// level 10
	,{ sf::Vector2f(blockLength, blockLength * incre1 * 0.7f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.7f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.7f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.7f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.0f) }
	});
sys::Matrix<sf::Color> LVDeploy::blockColorDeploy({
	// level 1
	{ sf::Color::Black, sf::Color::Blue, sf::Color::Black, sf::Color::Black
	, sf::Color::Green, sf::Color::Black, sf::Color::Cyan, sf::Color::Black
	, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan
	, sf::Color::Magenta, sf::Color::Black, sf::Color::Red, sf::Color::White
	, sf::Color::White, sf::Color::Black, sf::Color::White, sf::Color::Black }
	// level 2
	, { sf::Color::Black, sf::Color::Blue, sf::Color::Black, sf::Color::Black
	, sf::Color::Green, sf::Color::Black, sf::Color::Cyan, sf::Color::Black
	, sf::Color::White, sf::Color::Black, sf::Color::White, sf::Color::Black }
	// level 3
	, { sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan
	, sf::Color::Magenta, sf::Color::Black, sf::Color::Red, sf::Color::White
	, sf::Color::White, sf::Color::Black, sf::Color::White, sf::Color::Black }
	// level 4
	, { sf::Color::Black, sf::Color::Blue, sf::Color::Black, sf::Color::Black
	, sf::Color::Green, sf::Color::Black, sf::Color::Cyan, sf::Color::Black
	, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan
	, sf::Color::White, sf::Color::Black, sf::Color::White, sf::Color::Black }
	// level 5
	, { sf::Color::Green, sf::Color::Black, sf::Color::Cyan, sf::Color::Black
	, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan
	, sf::Color::Magenta, sf::Color::Black, sf::Color::Red, sf::Color::White
	, sf::Color::White, sf::Color::Black, sf::Color::White, sf::Color::Black }
	// level 6
	, { sf::Color::Black, sf::Color::Blue, sf::Color::Black, sf::Color::Black
	, sf::Color::Green, sf::Color::Black, sf::Color::Cyan, sf::Color::Black
	, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan
	, sf::Color::Magenta, sf::Color::Black, sf::Color::Red, sf::Color::White
	, sf::Color::White, sf::Color::Black, sf::Color::White, sf::Color::Black
	, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta, sf::Color::Black }
	// level 7
	, { sf::Color::Magenta, sf::Color::Blue, sf::Color::Black, sf::Color::Black
	, sf::Color::Green, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Black
	, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan
	, sf::Color::Magenta, sf::Color::Black, sf::Color::Magenta, sf::Color::White
	, sf::Color::White, sf::Color::Black, sf::Color::White, sf::Color::Magenta }
	// level 8
	, { sf::Color::Black, sf::Color::Red, sf::Color::Cyan, sf::Color::Black
	, sf::Color::Red, sf::Color::Black, sf::Color::Cyan, sf::Color::Black
	, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Red, sf::Color::White
	, sf::Color::White, sf::Color::Black, sf::Color::White, sf::Color::Red }
	// level 9
	, { sf::Color::Yellow, sf::Color::Blue, sf::Color::Black, sf::Color::Yellow
	, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan, sf::Color::Blue
	, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan
	, sf::Color::Magenta, sf::Color::Yellow, sf::Color::Red, sf::Color::Blue
	, sf::Color::White, sf::Color::Black, sf::Color::White, sf::Color::Yellow }
	// level 10
	, { sf::Color::Black, sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta
	, sf::Color::Green, sf::Color::Cyan, sf::Color::Cyan, sf::Color::Black
	, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Magenta
	, sf::Color::Magenta, sf::Color::Black, sf::Color::Red, sf::Color::White
	, sf::Color::White, sf::Color::Cyan, sf::Color::White, sf::Color::Black }
	});
sys::Matrix<sf::Vector2f> LVDeploy::blockSpeedDeploy({
	// level 1
	{ sf::Vector2f(1.5f, 0)
	, sf::Vector2f(-1.5f, 0)
	, sf::Vector2f(2.5f, 0)
	, sf::Vector2f(-2.5f, 0)
	, sf::Vector2f(3.f, 0) }
	// level 2
	, { sf::Vector2f(1.5f, 0)
	, sf::Vector2f(-1.5f, 0)
	, sf::Vector2f(3.f, 0) }
	// level 3
	, { sf::Vector2f(1.5f, 0)
	, sf::Vector2f(-2.5f, 0)
	, sf::Vector2f(3.f, 0) }
	// level 4
	, { sf::Vector2f(-1.5f, 0)
	, sf::Vector2f(2.5f, 0)
	, sf::Vector2f(-2.5f, 0)
	, sf::Vector2f(3.f, 0) }
	// level 5
	, { sf::Vector2f(1.5f, 0)
	, sf::Vector2f(-1.5f, 0)
	, sf::Vector2f(-2.5f, 0)
	, sf::Vector2f(3.f, 0) }
	// level 6
	, { sf::Vector2f(1.5f, 0)
	, sf::Vector2f(-1.5f, 0)
	, sf::Vector2f(2.5f, 0)
	, sf::Vector2f(-2.5f, 0)
	, sf::Vector2f(3.f, 0)
	, sf::Vector2f(-3.f, 0) }
	// level 7
	, { sf::Vector2f(1.5f, 0)
	, sf::Vector2f(-1.5f, 0)
	, sf::Vector2f(2.5f, 0)
	, sf::Vector2f(-2.5f, 0)
	, sf::Vector2f(3.f, 0) }
	// level 8
	, { sf::Vector2f(1.5f, 0)
	, sf::Vector2f(-1.5f, 0)
	, sf::Vector2f(2.5f, 0)
	, sf::Vector2f(-2.5f, 0)}
	// level 9
	, { sf::Vector2f(1.5f, 0)
	, sf::Vector2f(-1.5f, 0)
	, sf::Vector2f(2.5f, 0)
	, sf::Vector2f(-2.5f, 0)
	, sf::Vector2f(3.f, 0) }
	// level 10
	, { sf::Vector2f(1.5f, 0)
	, sf::Vector2f(-1.5f, 0)
	, sf::Vector2f(2.5f, 0)
	, sf::Vector2f(-2.5f, 0)
	, sf::Vector2f(3.f, 0) }
	});
sys::Matrix<float> LVDeploy::brickDeploy({
	// level 1
	{ 6, 60.f, 25.f, 1.f, 2.f, 3.f, 5.f }
	// level 2
	, { 2, 50.f, 30.f, 2.f, 2.f, 5.f, 4.f }
	// level 3
	,{ 3, 45.f, 20.f, 1.5f, 2.5f, 4.f, 3.f }
	// level 4
	,{ 4, 60.f, 25.f, 1.5f, 2.1f, 3.f, 2.f }
	// level 5
	,{ 5, 65.f, 35.f, 1.5f, 2.2f, 4.f, 4.f }
	// level 6
	,{ 3, 70.f, 35.f, 3.f, 2.3f, 3.f, 3.f }
	// level 7
	,{ 5, 75.f, 20.f, 2.5f, 2.5f, 5.f, 6.f }
	// level 8
	,{ 4, 70.f, 25.f, 2.f, 2.1f, 1.5f, 10.f }
	// level 9
	,{ 3, 73.f, 29.f, 1.5f, 2.4f, 3.f, 2.f }
	// level 10
	,{ 5, 40.f, 20.f, 1.5f, 2.5f, 5.f, 6.f }
	});

sys::Matrix<sf::Color> LVDeploy::brickColorDeploy({
	// level 1
	{ sf::Color(255, 183, 197) }
	// level 2
	, { sf::Color(rng() % 256, rng() % 256, rng() % 256) }
	// level 3
	, { sf::Color(rng() % 256, rng() % 256, rng() % 256) }
	// level 4
	, { sf::Color(rng() % 256, rng() % 256, rng() % 256) }
	// level 5
	, { sf::Color(rng() % 256, rng() % 256, rng() % 256) }
	// level 6
	, { sf::Color(rng() % 256, rng() % 256, rng() % 256) }
	// level 7
	, { sf::Color(rng() % 256, rng() % 256, rng() % 256) }
	// level 8
	, { sf::Color(rng() % 256, rng() % 256, rng() % 256) }
	// level 9
	, { sf::Color(rng() % 256, rng() % 256, rng() % 256) }
	// level 10
	, { sf::Color(rng() % 256, rng() % 256, rng() % 256) }
	});

void LVDeploy::finishLevel() noexcept {
	GameState::ready = false;
	GameState::start = false;
	GameState::finishLevel = true;
	std::cout << "Finished level: " << level++ << "!!!" << std::endl;
}

const std::vector<sf::Vector2f> LVDeploy::getBlockSLD() noexcept {
	std::vector<sf::Vector2f> temp;
	std::for_each(blockSideLengthDeploy.begin_row(level - 1), blockSideLengthDeploy.end_row(level - 1), [&](const sf::Vector2f &element) {
		temp.push_back(element);
	});
	return temp;
}

const std::vector<sf::Vector2f> LVDeploy::getBlockPD() noexcept {
	std::vector<sf::Vector2f> temp;
	std::for_each(blockPositionDeploy.begin_row(level - 1), blockPositionDeploy.end_row(level - 1), [&](const sf::Vector2f &element) {
		temp.push_back(element);
	});
	return temp;
}

const std::vector<sf::Color> LVDeploy::getBlockCD() noexcept {
	std::vector<sf::Color> temp;
	std::for_each(blockColorDeploy.begin_row(level - 1), blockColorDeploy.end_row(level - 1), [&](const sf::Color &element) {
		temp.push_back(element);
	});
	return temp;
}

const std::vector<sf::Vector2f> LVDeploy::getBlockSD() noexcept {
	std::vector<sf::Vector2f> temp;
	std::for_each(blockSpeedDeploy.begin_row(level - 1), blockSpeedDeploy.end_row(level - 1), [&](const sf::Vector2f &element) {
		temp.push_back(element);
	});
	return temp;
}

const std::vector<sf::Color> LVDeploy::getBrickCD() noexcept {
	std::vector<sf::Color> temp;
	std::for_each(brickColorDeploy.begin_row(level - 1), brickColorDeploy.end_row(level - 1), [&](const sf::Color &element) {
		temp.push_back(element);
	});
	return temp;
}

const std::vector<float> LVDeploy::getBrickD() noexcept {
	std::vector<float> temp;
	std::for_each(brickDeploy.begin_row(level - 1), brickDeploy.end_row(level - 1), [&](const float &element) {
		temp.push_back(element);
	});
	return temp;
}

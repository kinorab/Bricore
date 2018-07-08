#include "deploy.h"
#include "level.h"
#include "../../stuff/wall.h"
#include "../../stuff/ball.h"
#include "../../stuff/obstacle.h"
#include "../../stuff/player.h"
#include "../../definition/gameState.h"
#include "../../definition/utility.h"
#include <SFML/Graphics.hpp>

using namespace game;

Deploy::Deploy(Level * level)
	: level(level)
	, fBlockLength(100.f)
	, fSpan(3.f)
	, blockPositionDeploy({
		// level 1
		{ sf::Vector2f(fBlockLength, fBlockLength * fSpan)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f((LEVEL_WIDTH - fBlockLength) / 2 , (LEVEL_HEIGHT - fBlockLength * fSpan) / 2) }
		// level 2
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.75f) }
		// level 3
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.75f) }
		// level 4
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f((LEVEL_WIDTH - fBlockLength) / 2 , (LEVEL_HEIGHT - fBlockLength * fSpan) / 2) }
		// level 5
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f(fBlockLength * 2, fBlockLength * fSpan * 1.5f) }
		// level 6
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 4, fBlockLength * fSpan)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f((LEVEL_WIDTH - fBlockLength) / 2 , (LEVEL_HEIGHT - fBlockLength * fSpan) / 2) }
		// level 7
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f((LEVEL_WIDTH - fBlockLength) / 2 , (LEVEL_HEIGHT - fBlockLength * fSpan) / 2) }
		// level 8
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f((LEVEL_WIDTH - fBlockLength) / 2 , (LEVEL_HEIGHT - fBlockLength * fSpan) / 2) }
		// level 9
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f((LEVEL_WIDTH - fBlockLength) / 2 , (LEVEL_HEIGHT - fBlockLength * fSpan) / 2) }
		// level 10
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f(LEVEL_WIDTH - fBlockLength * 2, fBlockLength * fSpan * 1.75f)
		, sf::Vector2f((LEVEL_WIDTH - fBlockLength) / 2 , (LEVEL_HEIGHT - fBlockLength * fSpan) / 2) }
		})
	, blockSideLengthDeploy({
		// level 1
		{ sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.25f) }
		// level 2
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.2f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.2f) }
		// level 3
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.3f) }
		// level 4
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.7f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.6f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.25f) }
		// level 5
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.4f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.7f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.6f) }
		// level 6
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.1f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.3f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.f)
		, sf::Vector2f(fBlockLength * 2, fBlockLength * fSpan * 0.5f) }
		// level 7
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.6f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.4f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.6f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.f) }
		// level 8
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.5f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.4f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.6f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.75f) }
		// level 9
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.23f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.45f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.65f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.7f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.f) }
		// level 10
		, { sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.7f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.7f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.7f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 0.7f)
		, sf::Vector2f(fBlockLength, fBlockLength * fSpan * 1.0f) }
		})
	, blockColorDeploy({
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
		})
	, blockSpeedDeploy({
		// level 1
		{ sf::Vector2f(1.f, 0)
		, sf::Vector2f(-1.f, 0)
		, sf::Vector2f(2.f, 0)
		, sf::Vector2f(-2.f, 0)
		, sf::Vector2f(2.f, 0) }
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
		, sf::Vector2f(-2.5f, 0) }
		// level 9
		,{ sf::Vector2f(1.5f, 0)
		, sf::Vector2f(-1.5f, 0)
		, sf::Vector2f(2.5f, 0)
		, sf::Vector2f(-2.5f, 0)
		, sf::Vector2f(3.f, 0) }
		// level 10
		,{ sf::Vector2f(1.5f, 0)
		, sf::Vector2f(-1.5f, 0)
		, sf::Vector2f(2.5f, 0)
		, sf::Vector2f(-2.5f, 0)
		, sf::Vector2f(3.f, 0) }
		})
	, brickDeploy({
		// level 1
		{ 6, 60.f, 25.f, 1.f, 2.f, 3.f, 5.f }
		// level 2
		, { 2, 50.f, 30.f, 2.f, 2.f, 5.f, 4.f }
		// level 3
		, { 3, 45.f, 20.f, 1.5f, 2.5f, 4.f, 3.f }
		// level 4
		, { 4, 60.f, 25.f, 1.5f, 2.1f, 3.f, 2.f }
		// level 5
		, { 5, 65.f, 35.f, 1.5f, 2.2f, 4.f, 4.f }
		// level 6
		, { 3, 70.f, 35.f, 3.f, 2.3f, 3.f, 3.f }
		// level 7
		, { 5, 75.f, 20.f, 2.5f, 2.5f, 5.f, 6.f }
		// level 8
		, { 4, 70.f, 25.f, 2.f, 2.1f, 1.5f, 10.f }
		// level 9
		, { 3, 73.f, 29.f, 1.5f, 2.4f, 3.f, 2.f }
		// level 10
		, { 5, 40.f, 20.f, 1.5f, 2.5f, 5.f, 6.f }
		})
	, brickColorDeploy({
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
		}) {

}



const Deploy::ProxyBlock Deploy::getBlockDeploy() const noexcept {
	return ProxyBlock(blockPositionDeploy, blockSideLengthDeploy
		, blockColorDeploy, blockSpeedDeploy, level->getcurrentLevel());
}

const Deploy::ProxyBrick Deploy::getBrickDeploy() const noexcept {
	return ProxyBrick(brickColorDeploy, brickDeploy, level->getcurrentLevel());
}

Deploy::~Deploy() {
}

Deploy::ProxyBlock::ProxyBlock(const sys::Matrix<sf::Vector2f> & positionDeploy
	, const sys::Matrix<sf::Vector2f> & sideLengthDeploy
	, const sys::Matrix<sf::Color> & colorDeploy
	, const sys::Matrix<sf::Vector2f> & speedDeploy, const size_t currentLevel) {
	std::for_each(positionDeploy.begin_row(currentLevel - 1)
		, positionDeploy.end_row(currentLevel - 1), [&](const sf::Vector2f &element) {
		position.push_back(element);
	});
	std::for_each(sideLengthDeploy.begin_row(currentLevel - 1)
		, sideLengthDeploy.end_row(currentLevel - 1), [&](const sf::Vector2f &element) {
		sideLength.push_back(element);
	});
	std::for_each(colorDeploy.begin_row(currentLevel - 1)
		, colorDeploy.end_row(currentLevel - 1), [&](const sf::Color &element) {
		color.push_back(element);
	});
	std::for_each(speedDeploy.begin_row(currentLevel - 1)
		, speedDeploy.end_row(currentLevel - 1), [&](const sf::Vector2f &element) {
		speed.push_back(element);
	});
}

Deploy::ProxyBrick::ProxyBrick(const sys::Matrix<sf::Color>& colorDeploy
	, const sys::Matrix<float>& brickDeploy, const size_t currentLevel) {
	std::for_each(colorDeploy.begin_row(currentLevel - 1)
		, colorDeploy.end_row(currentLevel - 1), [&](const sf::Color &element) {
		color.push_back(element);
	});
	std::for_each(brickDeploy.begin_row(currentLevel - 1)
		, brickDeploy.end_row(currentLevel - 1), [&](const float &element) {
		it.push_back(element);
	});
}

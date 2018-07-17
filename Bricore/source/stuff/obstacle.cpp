#include "obstacle.h"
#include "ball.h"
#include "subPlayer.h"
#include "component/block.h"
#include "component/globular.h"
#include "../gameSys/level/level.h"
#include "../gameSys/level/area/zone.h"
#include "../event/eventListener.h"
#include "../definition/gameState.h"
#include "../definition/utility.h"
#include "../definition/intersects.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace item;
using namespace game;

Obstacle::Obstacle(const std::shared_ptr<game::Level> level) 
	: m_level(std::move(level)) {
	resettle();
	addListener(std::make_shared<EventListener<GameReadyEvent>>([this](auto & event) { onGameReady(event); }));
	addListener(std::make_shared<EventListener<GameFinishedLevelEvent>>([this](auto & event) { onGameFinishedLevel(event); }));
}

void Obstacle::resettle() {
	const std::vector<Vector2f> & position = m_level->deploy->getBlock().position;
	const std::vector<Vector2f> & sideLength = m_level->deploy->getBlock().sideLength;
	const size_t newSize = position.size();
	if (position.size() != sideLength.size()) {
		throw std::out_of_range("Position size not equal to side-length size.");
	}
	removeAllChildren();
	blocks.clear();
	for (size_t i = 0; i < newSize; ++i) {
		auto block = std::make_shared<Block>(position[i], sideLength[i]);
		addChild({ block });
		blocks.push_back(block);
	}
	using namespace game;
	auto &instance = Zone::getInstance();
	instance.settleZone(Zone::Obstacle, Vector2f(0.0f, instance.getZone(Zone::Wall).getSize().y + AREA_INTERVAL)
	, LEVEL_HEIGHT - (instance.getZone(Zone::Player).getSize().y + instance.getZone(Zone::Wall).getSize().y + 2 * AREA_INTERVAL));
	setAllVerticeColor(m_level->deploy->getBlock().color);
	setAllSpeed(m_level->deploy->getBlock().speed);
}


void Obstacle::update(const float updateRatio) {
	for (size_t i = 0; i < blocks.size(); ++i) {
		blocks[i]->update(updateRatio);
		blocksCollision(i);
		for (auto element : m_ball->enteredObstacleArea()) {
			element->isCollidedObstacle(blocks[i].get());
		}
	}
}

void Obstacle::resetCopyTarget(const std::shared_ptr<const SubPlayer> subPlayer, const std::shared_ptr<Ball> ball) {
	m_ball = std::move(ball);
	c_subPlayer = std::move(subPlayer);
}

void Obstacle::setBlockColor(const size_t number, const Color &c1, const Color &c2, const Color &c3, const Color &c4) {
	blocks[number]->setVerticeColor(c1, c2, c3, c4);
}

void Obstacle::setBlockColor(const size_t number, const Color & color) {
	blocks[number]->setVerticeColor(color);
}

void Obstacle::setAllColor(const std::vector<Color> & color) {
	for (size_t i = 0; i < blocks.size(); ++i) {
		blocks[i]->setVerticeColor(color[i]);
	}
}

void Obstacle::setAllVerticeColor(const std::vector<sf::Color> & vertice) {
	for (size_t i = 0, j = 1; i < blocks.size(); ++i, ++j) {
		blocks[i]->setVerticeColor(vertice[4 * j - 4], vertice[4 * j - 3], vertice[4 * j - 2], vertice[4 * j - 1]);
	}
}

void Obstacle::setBlockSpeed(const size_t number, const float speedX, const float speedY) {
	blocks[number]->setSpeed(speedX, speedY);
}

void Obstacle::setBlockSpeed(const size_t number, const Vector2f & speed) {
	blocks[number]->setSpeed(speed);
}

void Obstacle::setAllSpeed(const std::vector<Vector2f> & speed) {
	for (size_t i = 0; i < blocks.size(); ++i) {
		blocks[i]->setSpeed(speed[i]);
	}
}

void Obstacle::resetPosition() {
	for (size_t i = 0; i < blocks.size(); ++i) {
		blocks[i]->resetPosition();
	}
}

Obstacle::~Obstacle() {
	removeAllChildren(true);
	removeAllListener();
}

const Vector2f & Obstacle::getSpeed(const size_t number) const {
	return blocks[number]->getSpeed();
}

size_t Obstacle::getBlocksAmount() const {
	return blocks.size();
}

sys::DPointf Obstacle::getDP(const size_t number) const {
	return blocks[number]->getDP();
}

void Obstacle::draw(RenderTarget &target, RenderStates states) const {
	Container::draw(target, states);
}

void Obstacle::onGameReady(GameReadyEvent & event) {
	resetPosition();
}

void Obstacle::onGameFinishedLevel(GameFinishedLevelEvent & event) {
	resettle();
}

void Obstacle::blocksCollision(const size_t number) {
	for (size_t j = number + 1; j < blocks.size(); ++j) {
		if (sys::INCIntersects(blocks[number]->getDP(), blocks[j]->getDP())) {
			const Vector2f APos(blocks[number]->getPosition());
			const Vector2f BPos(blocks[j]->getPosition());
			const Vector2f ASpeed(blocks[number]->getSpeed());
			const Vector2f BSpeed(blocks[j]->getSpeed());
			if (APos.x > BPos.x) {
				if (APos.y > BPos.y) {
					blocks[number]->setSpeed(abs(ASpeed.x), abs(ASpeed.y));
					blocks[j]->setSpeed(-abs(BSpeed.x), -abs(BSpeed.y));
				}
				else {
					blocks[number]->setSpeed(abs(ASpeed.x), -abs(ASpeed.y));
					blocks[j]->setSpeed(-abs(BSpeed.x), abs(BSpeed.y));
				}
			}
			else {
				if (APos.y > BPos.y) {
					blocks[number]->setSpeed(-abs(ASpeed.x), abs(ASpeed.y));
					blocks[j]->setSpeed(abs(BSpeed.x), -abs(BSpeed.y));
				}
				else {
					blocks[number]->setSpeed(-abs(ASpeed.x), -abs(ASpeed.y));
					blocks[j]->setSpeed(abs(BSpeed.x), abs(BSpeed.y));
				}
			}
		}
	}
}

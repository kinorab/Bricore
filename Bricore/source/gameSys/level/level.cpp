#include "level.h"
#include "deploy.h"
#include "../../definition/gameState.h"
#include <iostream>
#include <stdexcept>

using namespace game;

bool Level::bInstance(false);

Level::Level(const Mode mode, const Diffculty diffculty, const size_t level)
	: uTotalLevel(100)
	, mode(mode)
	, diffculty(diffculty)
	, currentKind(NoChoose)
	, bDefaultControlKeySettled(false) {
	// instance is only one
	assert(!bInstance);
	bInstance = true;
	deploy.reset(new Deploy(this));
	if (level <= 0 && level > uTotalLevel) throw std::invalid_argument("Invalid level setting.");
	uCurrentLevel = level;
	if (mode == Mode::NoChoose || diffculty == Diffculty::NoChoose) return;
	settleKind(); 
}

void Level::changeSetting(const Mode mode, const Diffculty difficulty, const size_t level) {
	if (level <= 0 && level > uTotalLevel) throw std::invalid_argument("Invalid level setting.");
	uCurrentLevel = level;
	if (mode == Mode::NoChoose || diffculty == Diffculty::NoChoose) return;
	settleKind();
}

void Level::finishLevel() {
	currentState = GameState::LEVEL_FINISHED;
	if (uCurrentLevel < uTotalLevel) {
		std::cout << "Finished level: " << ++uCurrentLevel << "!!!" << std::endl;
		settleKind();
	}
	else {
		throw std::out_of_range("Is out of total level.");
	}
}

bool Level::isDefaultControlKeySettled() const {
	return bDefaultControlKeySettled;
}

size_t Level::getcurrentLevel() const {
	return uCurrentLevel;
}

size_t Level::getTotalLevel() const {
	return uTotalLevel;
}

Mode Level::getMode() const {
	return mode;
}

Diffculty Level::getDiffculty() const {
	return diffculty;
}

Level::~Level() {
}

void Level::settleKind() {
	const size_t control = uCurrentLevel % 10;
	switch (control) {
	case 0:
		currentKind = Boss;
		break;
	case 3:
		currentKind = Obstacle;
		break;
	case 5:
		currentKind = Bonus;
		break;
	case 8:
		currentKind = Iron;
		break;
	default:
		currentKind = Normal;
		break;
	}
}

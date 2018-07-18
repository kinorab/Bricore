#include "level.h"
#include "deploy.h"
#include "../data/data.h"
#include "../../definition/gameState.h"
#include <iostream>
#include <stdexcept>

using namespace game;

bool Level::bInstance(false);

Level::Level() noexcept
	: uTotalLevel(100)
	, currentMode()
	, currentDifficulty()
	, currentKind()
	, uCurrentLevel()
	, bDefaultControlKeySettled(false) {
	// instance is only one
	assert(!bInstance);
	bInstance = true;
	deploy.reset(new Deploy(this));
}

void Level::changeSetting(const Mode mode, const Diffculty difficulty) {
	currentMode = mode;
	currentDifficulty = difficulty;
	if (mode == Mode::_VSMode && difficulty == Diffculty::Not_StageMode) {
		uCurrentLevel = 0;
		currentKind = Kind::Not_StageMode;
		return;
	}
	uCurrentLevel = 1;
	settleKind();
}

void Level::changeSetting(const Data & saveData) {
}

void Level::finishLevel() {
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
	return currentMode;
}

Diffculty Level::getDiffculty() const {
	return currentDifficulty;
}

Level::Kind Level::getLevelKind() const {
	return currentKind;
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

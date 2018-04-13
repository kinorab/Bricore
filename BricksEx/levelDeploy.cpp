#include "levelDeploy.h"
#include "define.h"
#include <iostream>

size_t LVDeploy::level = 1;

LVDeploy::LVDeploy() { }

void LVDeploy::finishLevel() {
	GameState::ready = false;
	GameState::start = false;
	GameState::finishLevel = true;
	std::cout << "Finished level: " << level++ << "!!!" << std::endl;
}

const size_t LVDeploy::getLevel() {
	return level;
}

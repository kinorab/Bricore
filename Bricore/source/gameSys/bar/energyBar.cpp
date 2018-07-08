#include "energyBar.h"

using namespace game;

EnergyBar::EnergyBar(const size_t maxCount, const bool appear, const bool exist, const bool numberVisible)
	: BarSystem(maxCount, appear && exist, numberVisible && exist, exist) {
}

void EnergyBar::handleBar(const sf::Event * const event) {
}


EnergyBar::~EnergyBar() {
}

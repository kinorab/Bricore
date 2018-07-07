#include "energeBar.h"

using namespace game;

EnergeBar::EnergeBar(const size_t maxCount, const bool debut, const bool numberVisible)
	: BarSystem(maxCount, debut, numberVisible) {
}

void EnergeBar::handleBar(const sf::Event * const event) {
}


EnergeBar::~EnergeBar() {
}

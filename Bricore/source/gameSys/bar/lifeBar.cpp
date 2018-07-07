#include "lifeBar.h"

using namespace game;

LifeBar::LifeBar(const size_t maxCount, const bool debut, const bool numberVisible) 
	: BarSystem(maxCount, debut, numberVisible) {
}

void LifeBar::handleBar(const sf::Event * const event) {
}

LifeBar::~LifeBar() {
}

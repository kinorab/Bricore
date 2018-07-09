#include "lifeBar.h"

using namespace game;

LifeBar::LifeBar(const size_t maxCount, const bool appear, const bool exist, const bool numberVisible)
	: BarSystem(maxCount, appear && exist, numberVisible && exist, exist) {
}

void LifeBar::handleBar(const sf::Event * const event) {
}

LifeBar::~LifeBar() {
}

void LifeBar::draw(sf::RenderTarget &, sf::RenderStates) const {
}

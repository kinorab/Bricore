#include "rageBar.h"

using namespace game;

RageBar::RageBar(const size_t maxCount, const bool appear, const bool exist, const bool numberVisible)
	: BarSystem(maxCount, appear && exist, numberVisible && exist, exist) {
}

void RageBar::handleBar(const sf::Event * const event) {
}

RageBar::~RageBar() {
}

void RageBar::draw(sf::RenderTarget &, sf::RenderStates) const {
}

#include "subPlayer.h"
#include <SFML/Graphics.hpp>

SubPlayer::SubPlayer() {
}

void SubPlayer::update(const float intervalRate) {
}

SubPlayer::~SubPlayer() {
}

void SubPlayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
}

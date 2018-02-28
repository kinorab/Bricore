#include "rectangleShape.h"

game::RectangleShape::RectangleShape(const sf::Vector2f & size) :
	sf::RectangleShape(size) {

}

void game::RectangleShape::addEventListener() {
}

bool game::RectangleShape::dispatchEvent(game::Event * event) {
	return false;
}

bool game::RectangleShape::hasEventListener() const {
	return false;
}

void game::RectangleShape::removeEventListener() {
}

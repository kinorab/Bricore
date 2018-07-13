#include "attribute.h"
#include <SFML/Graphics.hpp>

using namespace game;

Attribute::Attribute(const Kind element)
	: withEffect(static_cast<AttributeEffect>(element))
	, it(element)
	, context(nullptr) {
}

Attribute::Attribute(const Kind element, const std::shared_ptr<sf::Texture> & texture)
	: withEffect(static_cast<AttributeEffect>(element))
	, it(element)
	, context(new sf::Sprite(*texture)) {
}

bool Attribute::containsPoint(const sf::Vector2f & point) const {
	if (!context) return false;
	return context->getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> Attribute::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void Attribute::setPosition(const sf::Vector2f & position) {
	context->setPosition(position);
}

void Attribute::setPosition(const float x, const float y) {
	context->setPosition(x, y);
}

void Attribute::setOrigin(const sf::Vector2f & origin) {
	context->setOrigin(origin);
}

void Attribute::setOrigin(const float x, const float y) {
	context->setOrigin(x, y);
}

const sf::Vector2f & Attribute::getPosition() const {
	return context->getPosition();
}

sf::FloatRect Attribute::getGlobalBounds() const {
	return context->getGlobalBounds();
}

sf::FloatRect Attribute::getLocalBounds() const {
	return context->getLocalBounds();
}

Attribute::~Attribute() {
}

void Attribute::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (!context) return;
	target.draw(*context, states);
}

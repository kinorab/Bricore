#include "effect.h"
#include <SFML/Graphics.hpp>

using namespace game;

Effect::Effect(const Kind effect, const bool isTargetItself)
	: it(effect)
	, context(nullptr)
	, bTargetItself(isTargetItself) {
}

Effect::Effect(const Kind effect, const std::shared_ptr<sf::Texture>& texture, const bool isTargetItself)
	: it(effect)
	, context(new sf::Sprite(*texture))
	, bTargetItself(isTargetItself) {
}

bool Effect::containsPoint(const sf::Vector2f & point) const {
	if (!context) return false;
	return context->getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> Effect::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void Effect::setPosition(const sf::Vector2f & position) {
	context->setPosition(position);
}

void Effect::setPosition(const float x, const float y) {
	context->setPosition(x, y);
}

void Effect::setOrigin(const sf::Vector2f & origin) {
	context->setOrigin(origin);
}

void Effect::setOrigin(const float x, const float y) {
	context->setOrigin(x, y);
}

const sf::Vector2f & Effect::getPosition() const {
	return context->getPosition();
}

sf::FloatRect Effect::getGlobalBounds() const {
	return context->getGlobalBounds();
}

sf::FloatRect Effect::getLocalBounds() const {
	return context->getLocalBounds();
}

Effect::~Effect() {
}

void Effect::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	if (!context) return;
	target.draw(*context, states);
}

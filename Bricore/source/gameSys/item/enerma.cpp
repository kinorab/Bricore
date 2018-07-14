#include "enerma.h"


using namespace item;

Enerma::Enerma(const Kind enerma, const std::shared_ptr<sf::Texture> & texture)
	: it(enerma)
	, bAppear(false)
	, context(new sf::Sprite(*texture)) {
}

bool Enerma::containsPoint(const sf::Vector2f & point) const {
	return context->getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> Enerma::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void Enerma::setAppear(const bool isAppear) {
	bAppear = isAppear;
}

void Enerma::setPosition(const sf::Vector2f & position) {
	context->setPosition(position);
}

void Enerma::setPosition(const float x, const float y) {
	context->setPosition(x, y);
}

void Enerma::setOrigin(const sf::Vector2f & origin) {
	context->setOrigin(origin);
}

void Enerma::setOrigin(const float x, const float y) {
	context->setOrigin(x, y);
}

const sf::Vector2f & Enerma::getPosition() const {
	return context->getPosition();
}

sf::FloatRect Enerma::getGlobalBounds() const {
	return context->getGlobalBounds();
}

sf::FloatRect Enerma::getLocalBonuds() const {
	return context->getLocalBounds();
}

Enerma::~Enerma() {
}

#include "attribute.h"
#include "../../manager/textureManager.h"
#include <SFML/Graphics.hpp>

using namespace game;

std::map<Attribute::Kind, std::string> Attribute::fileNames({
		std::pair(None, "none_attribute")
		, std::pair(Flame, "flame_attribute")
		, std::pair(Ice, "ice_attribute")
		, std::pair(Thunder, "thunder_attribute")
		, std::pair(Darkness, "darkness_attribute")
		, std::pair(Light, "light_attribute")
	});

Attribute::Attribute(const Kind element)
	: it(element) {
	auto attributeTexture = TextureManager::getInstance().get(fileNames[element]);
	//context.reset(new sf::Sprite(*attributeTexture));
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

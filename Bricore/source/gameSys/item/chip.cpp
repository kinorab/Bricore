#include "chip.h"
#include "../../manager/textureManager.h"
#include <SFML/Graphics.hpp>

using namespace item;

std::map<Chip::Kind, std::string> Chip::fileNames({
		std::pair(None, "none_chip")
		, std::pair(BurstChip, "burst_chip")
		, std::pair(FirearmChip, "firearm_chip")
		, std::pair(GuardChip, "guard_chip")
		, std::pair(HeraldChip, "herald_chip")
		, std::pair(LaserChip, "laser_chip")
	});

Chip::Chip(const Kind chip)
	: it(chip) {
	auto chipTexture = TextureManager::getInstance().get(fileNames[chip]);
	//context.reset(new sf::Sprite(*chipTexture));
}

bool Chip::containsPoint(const sf::Vector2f & point) const {
	if (!context) return false;
	return context->getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> Chip::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void Chip::setPosition(const sf::Vector2f & position) {
	context->setPosition(position);
}

void Chip::setPosition(const float x, const float y) {
	context->setPosition(x, y);
}

void Chip::setOrigin(const sf::Vector2f & origin) {
	context->setOrigin(origin);
}

void Chip::setOrigin(const float x, const float y) {
	context->setOrigin(x, y);
}

const sf::Vector2f & Chip::getPosition() const {
	return context->getPosition();
}

sf::FloatRect Chip::getLocalBounds() const {
	return context->getLocalBounds();
}

sf::FloatRect Chip::getGlobalBounds() const {
	return context->getGlobalBounds();
}

Chip::~Chip(){
}

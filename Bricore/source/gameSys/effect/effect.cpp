#include "effect.h"
#include "../../manager/textureManager.h"
#include <SFML/Graphics.hpp>

using namespace game;

std::map<Effect::Kind, std::string> Effect::fileNames({
		std::pair(Kind::Fragile, "fragile_effect")
		, std::pair(Kind::Hugify, "hugify_effect")
		, std::pair(Kind::Invisible, "invisible_effect")
		, std::pair(Kind::Invulnerable, "invulnerable_effect")
		, std::pair(Kind::Poison, "poison_effect")
		, std::pair(Kind::Shrink, "shrink_effect")
		, std::pair(Kind::SlowDown, "slowDown_effect")
		, std::pair(Kind::SpeedUp, "speedUp_effect")
		, std::pair(Kind::Sturdy, "sturdy_effect")
	});

Effect::Effect(const Kind effect, const bool isTargetItself)
	: it(effect)
	, bTargetItself(isTargetItself) {
	auto effectTexture = TextureManager::getInstance().get(fileNames[effect]);
	//context.reset(new sf::Sprite(*effectTexture));
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

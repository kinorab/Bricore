#include "effect.h"
#include "../../manager/textureManager.h"
#include <SFML/Graphics.hpp>

using namespace game;

std::map<Effect::Kind, std::string> Effect::fileNames({
		std::pair(Kind::Fragile, "effect/fragile")
		, std::pair(Kind::Hugify, "effect/hugify")
		, std::pair(Kind::Invisible, "effect/invisible")
		, std::pair(Kind::Invulnerable, "effect/invulnerable")
		, std::pair(Kind::Poison, "effect/poison")
		, std::pair(Kind::Shrink, "effect/shrink")
		, std::pair(Kind::SlowDown, "effect/slowDown")
		, std::pair(Kind::SpeedUp, "effect/speedUp")
		, std::pair(Kind::Sturdy, "effect/sturdy")
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

#include "enerma.h"
#include "../../manager/textureManager.h"

using namespace item;

std::map<Enerma::Kind, std::string> Enerma::fileNames({
		std::pair(AttackEnerma, "enerma/attack")
		, std::pair(CoolDownEnerma, "enerma/coolDown")
		, std::pair(DefendEnerma, "enerma/defend")
		, std::pair(HealEnerma, "enerma/heal")
		, std::pair(lifeEnerma, "enerma/life")
		, std::pair(ReviveEnerma, "enerma/revive")
	});

Enerma::Enerma(const Kind enerma)
	: it(enerma)
	, bAppear(false) {
	auto EnermaTexture = TextureManager::getInstance().get(fileNames[enerma]);
	context.reset(new sf::Sprite(*EnermaTexture));
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

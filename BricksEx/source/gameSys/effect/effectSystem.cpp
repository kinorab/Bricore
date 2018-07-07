#include "effectSystem.h"
#include <stdexcept>

using namespace game;

const sf::Time & EffectSystem::getDuration() const {
	return duration;
}

bool EffectSystem::isBelongToSkill() const {
	return bBelongToSkill;
}

bool EffectSystem::isExist() const {
	return bExist;
}

EffectSystem::~EffectSystem() {
}

EffectSystem::EffectSystem(const sf::Time &duration, const bool belongToSkill, const bool enable)
	: System(enable)
	, duration(duration)
	, elapsedTime(sf::seconds(0))
	, bBelongToSkill(belongToSkill)
	, bExist(true) {
}

void EffectSystem::setEnable(const bool enable) {
	if (!bExist) {
		throw std::invalid_argument("Effect not exist.");
	}
	if (isEnable() == enable) return;
	System::setEnable(enable);
	if (enable) {
		clock.restart();
		return;
	}
}

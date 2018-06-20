#include "effectSystem.h"
#include <stdexcept>

using namespace game;

const sf::Time & EffectSystem::getDuration() const {
	return duration;
}

bool EffectSystem::isBelongToSkill() const {
	return belongToSkill;
}

bool EffectSystem::isExist() const {
	return exist;
}

EffectSystem::~EffectSystem() {
}

EffectSystem::EffectSystem(const sf::Time &duration, const bool belongToSkill, const bool enable)
	: System(enable)
	, duration(duration)
	, elapsedTime(sf::seconds(0))
	, belongToSkill(belongToSkill)
	, exist(true) {
}

void EffectSystem::setEnable(const bool enable) {
	if (!exist) {
		throw std::invalid_argument("Effect not exist.");
	}
	if (isEnable() == enable) return;
	System::setEnable(enable);
	if (enable) {
		clock.restart();
		return;
	}
}

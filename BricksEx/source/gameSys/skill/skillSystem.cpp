#include "skillSystem.h"
#include "../effect/normalEffect.h"
#include <stdexcept>

using namespace game;

SkillSystem::SkillSystem(const sf::Time &duration, bool autoUse, const bool exist)
	: System(false)
	, autoUse(autoUse)
	, exist(exist)
	, duration(duration)
	, skillLevel(0)
	, status(Status::None)
	, elapsedTime(sf::seconds(0)){
}

void SkillSystem::selectOn() {
	if (status != Status::UnSelected) return;
	status = Status::Selected;
}

void SkillSystem::selectOff() {
	if (status != Status::Selected) return;
	status = Status::UnSelected;
}

void SkillSystem::setOwnToPlayer(const bool giveOwn) {
	if (!exist) throw std::invalid_argument("Skill not exist in setOwn.");

	if (giveOwn) {
		status = Status::UnSelected;
	}
	else {
		status = Status::None;
	}
}

void SkillSystem::setAutoUse(const bool autoUse) {
	this->autoUse = autoUse;
}

bool SkillSystem::isExist() const {
	return exist;
}

bool SkillSystem::isAutoUse() const {
	return autoUse;
}

const sf::Time & SkillSystem::getDuration() const {
	return duration;
}

const size_t SkillSystem::getSkillLevel() const {
	return skillLevel;
}

SkillSystem::~SkillSystem() {
}

void SkillSystem::useSkill() {
	if (isEnable()) return;
	setEnable(true);
	clock.restart();
}

void SkillSystem::elapsed() {
	if (!isEnable()) throw std::invalid_argument("Skill is disabled in elapsed.");
	if (elapsedTime >= duration) return;
	sf::Time distribute = clock.restart();
	elapsedTime += distribute;
	std::for_each(skillEffects.begin(), skillEffects.end(), [&](const std::shared_ptr<NormalEffect> effect) {
		if (effect->elapsedTime >= effect->duration) {
			effect->setEnable(false);
			return;
		};
		effect->elapsedTime += distribute;
	});
}

void SkillSystem::exhausted() {
	if (!isEnable()) throw std::invalid_argument("Skill is disabled in exhausted.");
	setEnable(false);
}

void SkillSystem::setEnable(const bool enable) {
	if (!exist) {
		throw std::invalid_argument("Skill not exist in setEnable.");
	}
	System::setEnable(enable);
	std::for_each(skillEffects.begin(), skillEffects.end(), [=](const std::shared_ptr<NormalEffect> &effect) {
		if (!effect->isExist()) {
			throw std::invalid_argument("Effect not exist in setEnable.");
		}
		effect->setEnable(enable);
	});
}

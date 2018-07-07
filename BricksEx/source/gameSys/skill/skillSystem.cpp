#include "skillSystem.h"
#include "../effect/entireEffect.h"
#include "../effect/attribute.h"
#include <stdexcept>

using namespace game;

SkillSystem::SkillSystem(const sf::Time &duration, bool autoUse, const bool exist)
	: System(false)
	, bAutoUse(autoUse)
	, bSilenced(false)
	, bLocked(false)
	, bExist(exist)
	, uLevel(0)
	, uMaxLevel(10)
	, duration(duration)
	, status(None)
	, elapsedTime(sf::seconds(0)){
}

bool SkillSystem::selectOn() {
	if (status != UnSelected) return false;
	status = Selected;
	return true;
}

bool SkillSystem::selectOff() {
	if (status != Selected) return false;
	status = UnSelected;
	return true;
}

void SkillSystem::upgradeSkill(const size_t number) {
	if (uLevel + number > uMaxLevel) throw std::out_of_range("Upgrade level over the max level.");
	uLevel += number;
}

void SkillSystem::extendMaxLevel(const size_t number) {
	uMaxLevel += number;
}

void SkillSystem::setOwnToPlayer(const bool giveOwn) {
	if (!bExist) throw std::invalid_argument("Skill not exist in setOwn.");

	if (giveOwn) {
		status = UnSelected;
	}
	else {
		status = None;
	}
}

void SkillSystem::setAutoUse(const bool autoUse) {
	bAutoUse = autoUse;
}

bool SkillSystem::isExist() const {
	return bExist;
}

bool SkillSystem::isAutoUse() const {
	return bAutoUse;
}

const sf::Time & SkillSystem::getDuration() const {
	return duration;
}

size_t SkillSystem::getLevel() const {
	return uLevel;
}

size_t SkillSystem::getmaxLevel() const {
	return uMaxLevel;
}

SkillSystem::~SkillSystem() {
}

void SkillSystem::useSkill() {
	if (isEnable()) return;
	setEnable(true);
	clock.restart();
}

bool SkillSystem::elapsed() {
	if (!isEnable()) throw std::invalid_argument("Skill was disabled in elapsed.");
	if (elapsedTime >= duration) return true;
	sf::Time distribute = clock.restart();
	elapsedTime += distribute;
	std::for_each(skillEffects.begin(), skillEffects.end(), [&](const std::shared_ptr<EntireEffect> effect) {
		if (effect->elapsedTime >= effect->duration) {
			effect->setEnable(false);
			return;
		};
		effect->elapsedTime += distribute;
	});
	return false;
}

void SkillSystem::exhausted() {
	if (!isEnable()) throw std::invalid_argument("Skill has been already disabled in exhausted.");
	setEnable(false);
}

void SkillSystem::setEnable(const bool enable) {
	if (!bExist) {
		throw std::invalid_argument("Skill not exist in setEnable.");
	}
	System::setEnable(enable);
	std::for_each(skillEffects.begin(), skillEffects.end(), [=](const std::shared_ptr<EntireEffect> &effect) {
		effect->setEnable(enable);
	});
}

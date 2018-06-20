#include "skillSystem.h"
#include "../effect/entireEffect.h"
#include "../effect/attribute.h"
#include <stdexcept>

using namespace game;

SkillSystem::SkillSystem(const sf::Time &duration, bool autoUse, const bool exist)
	: System(false)
	, autoUse(autoUse)
	, silenced(false)
	, locked(false)
	, exist(exist)
	, duration(duration)
	, level(0)
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
	if (level + number > maxLevel) throw std::out_of_range("Upgrade level over the max level.");
	level += number;
}

void SkillSystem::extendMaxLevel(const size_t number) {
	maxLevel += number;
}

void SkillSystem::setOwnToPlayer(const bool giveOwn) {
	if (!exist) throw std::invalid_argument("Skill not exist in setOwn.");

	if (giveOwn) {
		status = UnSelected;
	}
	else {
		status = None;
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

size_t SkillSystem::getLevel() const {
	return level;
}

size_t SkillSystem::getmaxLevel() const {
	return maxLevel;
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
	if (!exist) {
		throw std::invalid_argument("Skill not exist in setEnable.");
	}
	System::setEnable(enable);
	std::for_each(skillEffects.begin(), skillEffects.end(), [=](const std::shared_ptr<EntireEffect> &effect) {
		effect->setEnable(enable);
	});
}

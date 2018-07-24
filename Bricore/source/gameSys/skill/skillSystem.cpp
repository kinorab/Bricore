#include "skillSystem.h"
#include "../effect/effect.h"
#include "../attribute/attribute.h"
#include <stdexcept>
#include <algorithm>

using namespace game;

SkillSystem::SkillSystem(const sf::Time &duration, const bool exist)
	: System(false)
	, bSilenced(false)
	, bLocked(false)
	, bExist(exist)
	, uLevel(1)
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

void SkillSystem::setExist(const bool exist) {
	if (bExist == exist) throw std::invalid_argument("Exist state equal to parameter.");
	setEnable(isEnable() && exist);
	bExist = exist;
}

void SkillSystem::upgradeSkill(const size_t number) {
	if (uLevel + number > uMaxLevel) throw std::out_of_range("Upgrade level over the max level.");
	uLevel += number;
}

void SkillSystem::extendMaxLevel(const size_t number) {
	uMaxLevel += number;
}

bool SkillSystem::isExist() const {
	return bExist;
}

bool SkillSystem::isLocked() const {
	return bLocked;
}

bool SkillSystem::isSilenced() const {
	return bSilenced;
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
	bExist = false;
}

void SkillSystem::useSkill() {
	if (isEnable()) return;
	setEnable(true);
	clock.restart();
}

bool SkillSystem::elapsed() {
	if (!isEnable()) throw std::invalid_argument("Skill was disabled in elapsed.");
	if (elapsedTime >= duration) return true;
	clock.restart();
	return false;
}

void SkillSystem::exhausted() {
	if (!isEnable()) throw std::invalid_argument("Skill has been already disabled in exhausted.");
	setEnable(false);
}

#pragma warning(suppress: 26434)
void SkillSystem::setEnable(const bool enable) {
	if (!bExist) throw std::invalid_argument("Skill not exist in setEnable.");
	System::setEnable(enable);
}

#include "skillSystem.h"
#include "ballSkill.h"
#include "subPlayerSkill.h"
#include "playerSkill.h"
#include "../effect/effect.h"

using namespace game;

game::SkillSystem::SkillSystem()
	: exist(true) {
}

bool game::SkillSystem::isExist() const {
	return exist;
}

bool game::SkillSystem::isEnable() const {
	return enable;
}

const sf::Time & game::SkillSystem::getDuration() const {
	return duration;
}

const size_t game::SkillSystem::getSkillLevel() const {
	return skillLevel;
}

game::SkillSystem::~SkillSystem() {
}

void game::SkillSystem::setEnable(const bool enable) {
	this->enable = enable;
}

void game::SkillSystem::exhausted(SkillSystem *skill) {
	if (auto ballSkill = dynamic_cast<BallSkill *>(skill)) {
		ballSkill->setState(BallSkill::SkillState::None);
	}
	else if (auto playerSkill = dynamic_cast<PlayerSkill *>(skill)) {
		playerSkill->setState(PlayerSkill::SkillState::None);
	}
	else if (auto subPlayerSkill = dynamic_cast<SubPlayerSkill *>(skill)) {
		subPlayerSkill->setState(SubPlayerSkill::SkillState::None);
	}
	else {
		std::invalid_argument("Skill not exist.");
	}
	enable = false;
}


#include "skill.h"
#include "ballSkill.h"
#include "subPlayerSkill.h"
#include "playerSkill.h"
#include "effect.h"

using namespace game;

game::Skill::Skill()
	: exist(true) {
}

bool game::Skill::isExist() const {
	return exist;
}

bool game::Skill::isEnable() const {
	return enable;
}

const sf::Time & game::Skill::getDuration() const {
	return duration;
}

const size_t game::Skill::getSkillLevel() const {
	return skillLevel;
}

game::Skill::~Skill() {
}

void game::Skill::setEnable(const bool enable) {
	this->enable = enable;
}

void game::Skill::exhausted(Skill *skill) {
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


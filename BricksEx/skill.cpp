#include "skill.h"
#include "effect.h"

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


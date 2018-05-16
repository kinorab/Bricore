#include "skill.h"
#include "effect.h"

const bool & game::Skill::isExist() const {
	return exist;
}

const bool & game::Skill::isEnable() const {
	return enable;
}

game::Skill::~Skill() {
}

void game::Skill::setEnable(const bool enable) {
	this->enable = enable;
}

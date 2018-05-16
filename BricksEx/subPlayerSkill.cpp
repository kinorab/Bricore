#include "subPlayerSkill.h"
#include "effect.h"

game::SubPlayerSkill::SubPlayerSkill(const SubPlayer skill, const sf::Time & duration, const bool autoUse)
	: skill(skill) {
	this->duration = duration;
	setEnable(autoUse);
}

void game::SubPlayerSkill::gainSkill(const SubPlayer subPlayerSkill) {
}

game::SubPlayerSkill::~SubPlayerSkill() {
}

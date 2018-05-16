#include "playerSkill.h"

game::PlayerSkill::PlayerSkill(const Player skill, const sf::Time & duration, const bool autoUse)
	: skill(skill) {
	this->duration = duration;
	setEnable(autoUse);
}

void game::PlayerSkill::gainSkill(const Player playerSkill) {

}

game::PlayerSkill::~PlayerSkill() {
}

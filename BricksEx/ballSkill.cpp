#include "ballSkill.h"
#include "effect.h"

game::BallSkill::BallSkill(const Ball skill, const sf::Time & duration, const bool autoUse)
	: skill(skill) {
	this->duration = duration;
	setEnable(autoUse);
}

void game::BallSkill::gainSkill(const Ball ballSkill) {
}

game::BallSkill::~BallSkill() {
}

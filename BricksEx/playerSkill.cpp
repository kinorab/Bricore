#include "playerSkill.h"

game::PlayerSkill::PlayerSkill(const Player skillName, const sf::Time & duration, const bool autoUse)
	: skillName(skillName) {
	this->duration = duration;
	setEnable(autoUse);
}

void game::PlayerSkill::useSkill()
{
}

void game::PlayerSkill::upgradeSkill()
{
}

void game::PlayerSkill::gainSkill(const Player playerSkill) {

}

game::Skill::Player game::PlayerSkill::getSkillName() const {
	return skillName;
}

const sf::Sprite & game::PlayerSkill::getSkill() const {
	return skill;
}

game::PlayerSkill::~PlayerSkill() {
}

void game::PlayerSkill::handleSkill()
{
}

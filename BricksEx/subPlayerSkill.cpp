#include "subPlayerSkill.h"
#include "effect.h"

game::SubPlayerSkill::SubPlayerSkill(const SubPlayer skillName, const sf::Time & duration, const bool autoUse)
	: skillName(skillName) {
	this->duration = duration;
	setEnable(autoUse);
}

void game::SubPlayerSkill::useSkill()
{
}

void game::SubPlayerSkill::upgradeSkill()
{
}

void game::SubPlayerSkill::gainSkill(const SubPlayer skillName) {
}

game::Skill::SubPlayer game::SubPlayerSkill::getSkillName() const {
	return skillName;
}

const sf::Sprite & game::SubPlayerSkill::getSkill() const {
	return skill;
}

game::SubPlayerSkill::~SubPlayerSkill() {
}

void game::SubPlayerSkill::handleSkill()
{
}

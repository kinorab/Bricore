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

void game::SubPlayerSkill::loadSkillPicture(const std::vector<std::string>& fileName) {

}

game::Skill::SubPlayer game::SubPlayerSkill::getSkillName() const {
	return skillName;
}

game::SubPlayerSkill::~SubPlayerSkill() {
}

void game::SubPlayerSkill::handleSkill()
{
}

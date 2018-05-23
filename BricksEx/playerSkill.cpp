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

void game::PlayerSkill::loadSkillPicture(const std::vector<std::string>& fileName)
{
}

game::Skill::Player game::PlayerSkill::getSkillName() const {
	return skillName;
}

game::PlayerSkill::~PlayerSkill() {
}

void game::PlayerSkill::handleSkill()
{
}

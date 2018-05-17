#include "ballSkill.h"
#include "effect.h"

std::vector<sf::Image> game::BallSkill::frame;

game::BallSkill::BallSkill(const Ball skillName, const sf::Time & duration, const bool autoUse)
	: skillName(skillName) {
	this->duration = duration;
	setEnable(autoUse);
}

void game::BallSkill::useSkill()
{
}

void game::BallSkill::upgradeSkill()
{
}

void game::BallSkill::gainSkill(const Ball skillName) {
}

void game::BallSkill::setFrame(const size_t level) {
}

game::Skill::Ball game::BallSkill::getSkillName() const {
	return Ball();
}

const sf::Sprite & game::BallSkill::getSkill() const {
	return skill;
}

game::BallSkill::~BallSkill() {
}

void game::BallSkill::handleSkill()
{
}

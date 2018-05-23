#include "ballSkill.h"
#include "effect.h"
#include <SFML/Graphics.hpp>

std::map<size_t, std::shared_ptr<sf::Texture>> game::BallSkill::frames;

game::BallSkill::BallSkill(const Ball skillName, const sf::Time & duration, const bool autoUse)
	: skill(skillName, Picture()) {
	this->duration = duration;
	setEnable(autoUse);
}

void game::BallSkill::loadFrame(const std::map<size_t, std::string> &fileNames) {
	std::for_each(fileNames.begin(), fileNames.end(), [&](const std::pair<size_t, std::string> &file) {
		frames.emplace(file.first, std::shared_ptr<sf::Texture>(new sf::Texture()));
		frames.at(file.first)->loadFromFile(file.second);
	});
}

void game::BallSkill::swapSkill(BallSkill & other) {
	skill.swap(other.skill);
	statePreviews.swap(other.statePreviews);
}

void game::BallSkill::useSkill()
{
}

void game::BallSkill::upgradeSkill()
{
}

void game::BallSkill::gainSkill(const Ball skillName) {
}

void game::BallSkill::loadSkillPicture(const std::vector<std::string>& fileName)
{
}

game::Skill::Ball game::BallSkill::getSkillName() const {
	return skill.first;
}

game::BallSkill::~BallSkill() {
}

void game::BallSkill::draw(sf::RenderTarget &, sf::RenderStates) const
{
}

void game::BallSkill::handleSkill()
{
}

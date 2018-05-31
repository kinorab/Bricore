#include "playerSkill.h"
#include <SFML/Graphics.hpp>

using namespace game;

PlayerSkill::PlayerSkill(const Player skillName, const std::vector<NormalEffect> &normalEffects, const sf::Time & duration, const bool autoUse)
	: skill(skillName, Picture()) {
	this->duration = duration;
	setEnable(autoUse);
	skill.second.currentState = SkillState::None;
	std::for_each(normalEffects.begin(), normalEffects.end(), [&](const NormalEffect normalEffect) {
		skillEffects.push_back(std::shared_ptr<Effect>(new Effect(normalEffect, this)));
	});
}

void PlayerSkill::swapSkill(PlayerSkill & other) {
	skill.swap(other.skill);
	statePreviews.swap(other.statePreviews);
}

void PlayerSkill::useSkill() {
}

void PlayerSkill::upgradeSkill() {
}

void PlayerSkill::loadSkillPicture(const std::map<SkillState, std::string> &fileNames, const bool isSmooth) {
	std::for_each(fileNames.begin(), fileNames.end(), [&](const std::pair<SkillState, std::string> &fileName) {
		statePreviews.at(fileName.first)->loadFromFile(fileName.second);
		statePreviews.at(fileName.first)->setSmooth(isSmooth);
	});
}

void PlayerSkill::setState(const SkillState state) {
	skill.second.currentState = state;
	skill.second.context.reset(new sf::Sprite(*statePreviews.at(state)));
}

PlayerSkill::SkillState PlayerSkill::getState() const {
	return skill.second.currentState;
}

SkillSystem::Player PlayerSkill::getSkillName() const {
	return skill.first;
}

PlayerSkill::~PlayerSkill() {
}

void PlayerSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(*skill.second.context, states);
}

void PlayerSkill::handleSkill() {
}

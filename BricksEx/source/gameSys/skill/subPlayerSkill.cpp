#include "subPlayerSkill.h"
#include <SFML/Graphics.hpp>

using namespace game;

SubPlayerSkill::SubPlayerSkill(const SubPlayer skillName, const std::vector<NormalEffect> &normalEffects, const sf::Time & duration, const bool autoUse)
	: skill(skillName, Picture()) {
	this->duration = duration;
	setEnable(autoUse);
	skill.second.currentState = SkillState::None;
	std::for_each(normalEffects.begin(), normalEffects.end(), [&](const NormalEffect normalEffect) {
		skillEffects.push_back(std::shared_ptr<Effect>(new Effect(normalEffect, this)));
	});
}

void SubPlayerSkill::swapSkill(SubPlayerSkill & other) {
	skill.swap(other.skill);
	statePreviews.swap(other.statePreviews);
}

void SubPlayerSkill::useSkill() {
}

size_t SubPlayerSkill::upgradeSkill() {
	return skillLevel++;
}

void SubPlayerSkill::loadPreviewFile(const std::map<SkillState, std::string> &fileNames, const bool isSmooth) {
	std::for_each(fileNames.begin(), fileNames.end(), [&](const std::pair<SkillState, std::string> &fileName) {
		statePreviews.at(fileName.first)->loadFromFile(fileName.second);
		statePreviews.at(fileName.first)->setSmooth(isSmooth);
	});
}

void SubPlayerSkill::setState(const SkillState state) {
	skill.second.currentState = state;
	skill.second.context.reset(new sf::Sprite(*statePreviews.at(state)));
}

SubPlayerSkill::SkillState SubPlayerSkill::getState() const {
	return skill.second.currentState;
}

SkillSystem::SubPlayer SubPlayerSkill::getSkillName() const {
	return skill.first;
}

SubPlayerSkill::~SubPlayerSkill() {
}

void SubPlayerSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(*skill.second.context, states);
}

void SubPlayerSkill::handleSkill() {
}

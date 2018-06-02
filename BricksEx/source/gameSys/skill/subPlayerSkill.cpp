#include "subPlayerSkill.h"
#include "../effect/normalEffect.h"
#include <SFML/Graphics.hpp>

using namespace game;

size_t SubPlayerSkill::maximumCarry(1);
size_t SubPlayerSkill::currentCarry(0);

SubPlayerSkill::SubPlayerSkill(const SubPlayer skillName, const std::vector<Normal> &normalEffects, const sf::Time & duration, const bool autoUse)
	: skill(skillName, Picture())
	, SkillSystem(duration, autoUse) {
	skill.second.currentState = SkillState::None;
	std::for_each(normalEffects.begin(), normalEffects.end(), [&](const Normal normalEffect) {
		skillEffects.push_back(std::shared_ptr<NormalEffect>(new NormalEffect(normalEffect, this)));
	});
}

void SubPlayerSkill::swapSkill(SubPlayerSkill & other) {
	skill.swap(other.skill);
	statePreviews.swap(other.statePreviews);
}

void SubPlayerSkill::handleSkill(const sf::Event * const event) {
}

void SubPlayerSkill::handleSelect(const sf::Event * const event) {
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

size_t SubPlayerSkill::getMaximumCarry() const {
	return maximumCarry;
}

size_t SubPlayerSkill::getCurrentCarry() const {
	return currentCarry;
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

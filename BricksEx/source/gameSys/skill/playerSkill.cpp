#include "playerSkill.h"
#include "../effect/normalEffect.h"
#include <SFML/Graphics.hpp>

using namespace game;

size_t PlayerSkill::maximumCarry(3);
size_t PlayerSkill::currentCarry(0);

PlayerSkill::PlayerSkill(const Player skillName, const std::vector<Normal> &normalEffects, const sf::Time & duration, const bool autoUse)
	: skill(skillName, Picture())
	, SkillSystem(duration, autoUse) {
	skill.second.currentState = SkillState::None;
	std::for_each(normalEffects.begin(), normalEffects.end(), [&](const Normal normalEffect) {
		skillEffects.push_back(std::shared_ptr<NormalEffect>(new NormalEffect(normalEffect, this)));
	});
}

void PlayerSkill::swapSkill(PlayerSkill &other) {
	skill.swap(other.skill);
	statePreviews.swap(other.statePreviews);
}

void PlayerSkill::extendCarry(const size_t number) {
	maximumCarry += number;
}

size_t PlayerSkill::upgradeSkill() {
	return skillLevel++;
}

void PlayerSkill::handleSkill(const sf::Event * const event) {
	if (skill.second.currentState == SkillState::None || status == Status::None) return;

	if (skill.second.currentState == SkillState::OnMiniField) {

	}
	else if (skill.second.currentState == SkillState::OnField) {

	}
	else if (skill.second.currentState == SkillState::Using) {

	}
	else if (skill.second.currentState == SkillState::Locked) {

	}
}

void PlayerSkill::handleSelect(const sf::Event * const event) {
	if (status == Status::None) return;
}

void PlayerSkill::loadPreviewFile(const std::map<SkillState, std::string> &fileNames, const bool isSmooth) {
	std::for_each(fileNames.begin(), fileNames.end(), [&](const std::pair<SkillState, std::string> &fileName) {
		statePreviews.at(fileName.first)->loadFromFile(fileName.second);
		statePreviews.at(fileName.first)->setSmooth(isSmooth);
	});
}

void PlayerSkill::setState(const SkillState state) {
	skill.second.currentState = state;
	skill.second.context.reset(new sf::Sprite(*statePreviews.at(state)));
}

size_t PlayerSkill::getMaximumCarry() const {
	return maximumCarry;
}

size_t PlayerSkill::getCurrentCarry() const {
	return currentCarry;
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

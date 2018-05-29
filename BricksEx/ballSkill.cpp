#include "ballSkill.h"
#include <SFML/Graphics.hpp>

using namespace game;

std::map<size_t, std::shared_ptr<sf::Texture>> BallSkill::frames;

BallSkill::BallSkill(const Ball skillName, const std::vector<NormalEffect> &normalEffects, const sf::Time & duration, const bool autoUse)
	: skill(skillName, Picture()) {
	this->duration = duration;
	setEnable(autoUse);
	skill.second.currentState = SkillState::No_Buy;
	std::for_each(normalEffects.begin(), normalEffects.end(), [&](const NormalEffect normalEffect) {
		skillEffects.push_back(std::shared_ptr<Effect>(new Effect(normalEffect, this)));
	});
}

void BallSkill::loadFrame(const std::map<size_t, std::string> &fileNames) {
	std::for_each(fileNames.begin(), fileNames.end(), [&](const std::pair<size_t, std::string> &file) {
		frames.emplace(file.first, std::shared_ptr<sf::Texture>(new sf::Texture()));
		frames.at(file.first)->loadFromFile(file.second);
	});
}

void BallSkill::swapSkill(BallSkill & other) {
	skill.swap(other.skill);
	statePreviews.swap(other.statePreviews);
}

void BallSkill::useSkill() {
}

void BallSkill::upgradeSkill() {
}

void BallSkill::loadSkillPicture(const std::map<SkillState, std::string> &fileNames, const bool isSmooth) {
	std::for_each(fileNames.begin(), fileNames.end(), [&](const std::pair<SkillState, std::string> &fileName) {
		statePreviews.at(fileName.first)->loadFromFile(fileName.second);
		statePreviews.at(fileName.first)->setSmooth(isSmooth);
	});
}

void BallSkill::setState(const SkillState state) {
	auto context = skill.second.context;
	auto frame = skill.second.frame;
	skill.second.currentState = state;
	context.reset(new sf::Sprite(*statePreviews.at(state)));
	if (state == SkillState::OnDropping) {
		frame.reset(new sf::Sprite(*frames.at(skillLevel-1)));
		context->setOrigin(context->getTexture()->getSize().x / 2.f, context->getTexture()->getSize().y / 2.f);
		context->setPosition(frame->getTexture()->getSize().x / 2.f, frame->getTexture()->getSize().y / 2.f);
	}
	else if(frame){
		frame = nullptr;
	}
}

BallSkill::SkillState BallSkill::getState() const {
	return skill.second.currentState;
}

Skill::Ball BallSkill::getSkillName() const {
	return skill.first;
}

BallSkill::~BallSkill() {
}

void BallSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(*skill.second.context, states);
	if (skill.second.frame) {
		target.draw(*skill.second.frame, states);
	}
}

void BallSkill::handleSkill() {
}

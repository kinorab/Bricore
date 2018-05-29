#include "effect.h"
#include "skill.h"
#include "ballSkill.h"
#include "playerSkill.h"
#include "subPlayerSkill.h"

using namespace game;

Effect::Effect(const Normal effect, const sf::Time duration)
	: exist(true)
	, isBelongToSkill(false)
	, normalEffect(effect)
	, duration(duration) {
}

Effect::Effect(const Normal effect, const Skill * skill) {
	if (auto ballSkill = dynamic_cast<const BallSkill *>(skill)) {

	}
	else if (auto playerSkill = dynamic_cast<const PlayerSkill *>(skill)) {

	}
	else if (auto subPlayerSkill = dynamic_cast<const SubPlayerSkill *>(skill)) {

	}
	else {
		throw std::invalid_argument("Skill not exist.");
	}
	duration = skill->getDuration();
	normalEffect = effect;
	exist = true;
	isBelongToSkill = true;
}

void Effect::handleEffect(const float elapsed) {
	duration -= sf::seconds(elapsed);
	if (duration.asSeconds() <= 0.0f) {
		exist = false;
	}
}

Effect::Effect()
	: exist(true) {
}

void Effect::handleEffect(Skill * skill) {
	skill->isExist();
}

const bool & Effect::isExist() const {
	return exist;
}

const NormalEffect & Effect::getNormalEffect() const {
	return normalEffect;
}

const sf::Time & Effect::getDuration() const {
	return duration;
}

Effect::~Effect() { }

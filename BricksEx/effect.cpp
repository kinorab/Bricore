#include "effect.h"
#include "skill.h"

game::Effect::Effect(const Normal effect, const bool isSkill, const sf::Time duration)
	: exist(true) {
	if (isSkill) {
		currentNormalE = effect;
	}
	else {
		currentNormalE = effect;
		this->duration = duration;
	}
}

void game::Effect::handleEffect(const float elapsed) {
	duration -= sf::seconds(elapsed);
	if (duration.asSeconds() <= 0.0f) {
		exist = false;
	}
}

game::Effect::Effect()
	: exist(true) {
}

void game::Effect::handleEffect(Skill & skill) {
	skill.isExist();
}

const bool & game::Effect::isExist() const {
	return exist;
}

const game::NormalE & game::Effect::getNormalEffect() const {
	return currentNormalE;
}

const sf::Time & game::Effect::getDuration() const {
	return duration;
}

game::Effect::~Effect() { }

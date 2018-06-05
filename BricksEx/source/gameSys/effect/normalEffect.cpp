#include "normalEffect.h"
#include "../skill/skillSystem.h"

using namespace game;

NormalEffect::NormalEffect(const Normal effect, const sf::Time duration)
	: EffectSystem(duration, false)
	, normalEffect(effect) {
}

NormalEffect::NormalEffect(const Normal effect, const SkillSystem * const skill)
	: EffectSystem(skill->getDuration(), true, skill->isEnable())
	, normalEffect(effect) {
}

const Normal & NormalEffect::getNormalEffect() const {
	return normalEffect;
}

NormalEffect::~NormalEffect() {
}
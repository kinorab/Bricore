#include "entireEffect.h"
#include "effect.h"
#include "../skill/skillSystem.h"
#include "../../definition/gameState.h"
#include <SFML/System.hpp>

using namespace game;

EntireEffect::EntireEffect(const EffectKind<Effect>::Kind effect, const sf::Time &duration)
	: EffectSystem(duration, false, false, true)
	, effect(std::shared_ptr<Effect>(new Effect(effect))){
}

EntireEffect::EntireEffect(const EffectKind<Effect>::Kind effect, const SkillSystem * const skill)
	: EffectSystem(skill->getDuration(), true, skill->isEnable(), skill->isExist()) {
}

const EffectKind<Effect>::Kind EntireEffect::getEffect() const {
	return effect->it;
}

EntireEffect::~EntireEffect() {
}

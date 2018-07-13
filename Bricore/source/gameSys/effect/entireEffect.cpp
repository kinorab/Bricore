#include "entireEffect.h"
#include "effect.h"
#include "../skill/skillSystem.h"
#include "../../definition/gameState.h"
#include <SFML/System.hpp>

using namespace game;

EntireEffect::EntireEffect(const EffectKind<Effect>::Kind effect, const sf::Time &duration
	, const bool isTargetItself, const bool exist)
	: EffectSystem(duration, false, false, exist)
	, effect(std::shared_ptr<Effect>(new Effect(effect, isTargetItself))) {
}

EntireEffect::EntireEffect(const EffectKind<Effect>::Kind effect, const SkillSystem * const skill
	, const bool isTargetItself)
	: EffectSystem(skill->getDuration(), true, skill->isEnable(), skill->isExist()) {
}

std::shared_ptr<Effect> EntireEffect::getEffect() const {
	return effect;
}

EntireEffect::~EntireEffect() {
}

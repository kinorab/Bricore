#pragma once
#include "effectSystem.h"
#include "effect.h"

namespace game {
	class SkillSystem;

	class EntireEffect : 
		public EffectSystem {
		friend class SkillSystem;
	public:
		explicit EntireEffect(const EffectKind<Effect>::Kind effect, const sf::Time &duration
			, const bool isTargetItself, const bool exist);
		explicit EntireEffect(const EffectKind<Effect>::Kind effect, const SkillSystem * const skill
			, const bool isTargetItself);
		std::shared_ptr<Effect> getEffect() const;
		virtual ~EntireEffect();

	private:
		std::shared_ptr<Effect> effect;
	};
}

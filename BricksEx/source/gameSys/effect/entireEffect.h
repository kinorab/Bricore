#pragma once
#include "effectSystem.h"
#include "effect.h"
#include <memory>

namespace game {
	class SkillSystem;

	class EntireEffect : 
		public EffectSystem {
		friend class SkillSystem;
	public:
		explicit EntireEffect(const EffectKind<Effect>::Kind effect, const sf::Time &duration);
		explicit EntireEffect(const EffectKind<Effect>::Kind effect, const SkillSystem * const skill);
		const EffectKind<Effect>::Kind getEffect() const;
		virtual ~EntireEffect();

	private:
		void setEnable(const bool enable);
		std::shared_ptr<Effect> effect;
	};
}

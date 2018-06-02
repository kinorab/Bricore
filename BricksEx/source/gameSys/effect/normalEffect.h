#pragma once

#include <SFML/System/Time.hpp>
#include "effectSystem.h"

namespace game {
	class SkillSystem;

	class NormalEffect : public EffectSystem {
		friend class SkillSystem;
	public:
		explicit NormalEffect(const Normal effect, const sf::Time duration);
		explicit NormalEffect(const Normal effect, const SkillSystem * const skill);
		virtual const Normal & getNormalEffect() const;
		virtual ~NormalEffect();

	private:
		Normal normalEffect;
	};
}

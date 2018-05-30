#pragma once

#include "../system.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <vector>

namespace game {
	class Effect;

	class SkillSystem : public System {
	public:
		enum class Player {
			None,
			AmbitGuard,
			DropRateUp,
			EnergyRush,
		};
		// skill difference with subPlayer's type
		enum class SubPlayer {
			None,
			ForceField,
			ForceShield,
			EnergyRush,
			InfinitePower,
			MagicalField,
			MagicalShield,
		};
		enum class Ball {
			None,
			HugeBody,
			IronBody,
			MultipleAttack,
			ShieldGuard,
			ShuttleSpace
		};
		// for stable version release
		enum class Attribute {
			None,
			Darkness,
			Flame,
			Ice,
			Light,
			Poison,
			Thunder
		};
		virtual void useSkill() = 0;
		virtual void upgradeSkill() = 0;
		virtual bool isExist() const;
		virtual bool isEnable() const;
		virtual const sf::Time & getDuration() const;
		virtual const size_t getSkillLevel() const;
		virtual ~SkillSystem();

	protected:
		SkillSystem();
		virtual void handleSkill() = 0;
		virtual void setEnable(const bool);
		virtual void exhausted(SkillSystem *);
		sf::Time duration;
		size_t skillLevel;
		std::vector<std::shared_ptr<Effect>> skillEffects;

	private:
		bool enable;
		bool exist;
	};
}

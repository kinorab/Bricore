#pragma once

#include "../system.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <vector>

namespace sf {
	class Event;
}

namespace game {
	class NormalEffect;

	class SkillSystem : 
		public System {
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
			EnergyRush,
			ForceField,
			ForceShield,
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
			ShuttleSpace,
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
		// return level before upgraded
		virtual size_t upgradeSkill() = 0;
		virtual void handleSkill(const sf::Event * const event) = 0;
		virtual void handleSelect(const sf::Event * const event) = 0;
		virtual void setOwnToPlayer(const bool giveOwn = true);
		virtual void setAutoUse(const bool autoUse);

		virtual bool isExist() const;
		virtual bool isAutoUse() const;
		virtual const sf::Time & getDuration() const;
		virtual const size_t getSkillLevel() const;
		virtual ~SkillSystem();

	protected:
		enum class Status {
			None,			// not own the skill yet
			Selected,		// selected skill in current level
			UnSelected		// unselected skill in current level
		};
		SkillSystem(const sf::Time &duration, bool autoUse = false, const bool exist = true);
		virtual void selectOn();
		virtual void selectOff();
		virtual void useSkill();
		virtual void elapsed();
		virtual void exhausted();
		
		sf::Time duration;
		sf::Time elapsedTime;
		size_t skillLevel;
		std::vector<std::shared_ptr<NormalEffect>> skillEffects;
		Status status;
		bool autoUse;

	private:
		virtual void setEnable(const bool enable) override;
		// used to checkout in particular mode
		bool exist;
	};
}

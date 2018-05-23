#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <vector>

namespace game {
	class Effect;

	class Skill {
	public:
		enum class Player {
			None,
		};
		enum class SubPlayer {
			None,
			ForceField,
			ForceShield,
			InfinitePower,

		};
		enum class Ball {
			None,
			MultipleAttack,
			ShieldGuard,
			IronPower,
			HugeBody,
			ShuttleSpace
		};
		// for stable version release
		enum class Attribute {
			None,
			Poison,
			Flame,
			Ice,
			Thunder,
			Light,
			Darkness
		};
		Skill();
		virtual void useSkill() = 0;
		virtual void upgradeSkill() = 0;
		virtual void loadSkillPicture(const std::vector<std::string> &fileName) = 0;
		virtual bool isExist() const;
		virtual bool isEnable() const;
		virtual const sf::Time & getDuration() const;
		virtual const size_t getSkillLevel() const;
		virtual ~Skill();

	protected:
		virtual void handleSkill() = 0;
		virtual void setEnable(const bool);
		sf::Time duration;
		size_t skillLevel;
		std::vector<std::shared_ptr<Effect>> skillEffects;

	private:
		bool enable;
		bool exist;
	};
}

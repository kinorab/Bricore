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
		};
		enum class Ball {
			None,
			Multiple,
			Shield,
			Iron,
			Hugify
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
		virtual void useSkill() = 0;
		virtual void upgradeSkill() = 0;
		virtual const bool & isExist() const;
		virtual const bool & isEnable() const;
		virtual ~Skill();

	protected:
		virtual void setEnable(const bool);
		sf::Time duration;
		size_t skillLevel;
		std::vector<std::shared_ptr<Effect>> skillEffects;

	private:
		bool enable;
		bool exist;
	};
}

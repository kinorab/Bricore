#pragma once
#include <SFML/System/Time.hpp>

namespace game {
	class Skill;

	class Effect {
	public:
		enum class Normal {
			None,
			SlowDown,
			SpeedUp,
			Gravity,
			Fragile,
			Sturdy,
			Magnetic,
			Invincible,
			Invisible
		};
		// for stable version release
		enum class Attribute {
			None,
			Poisoning,			// poison
			Combustion,			// flame
			Frozen,				// ice
			Paralysis,			// thunder
			Dazzling,			// light
			Blind				// darkness
		};
		explicit Effect(const Normal effect, const bool isSkill, const sf::Time duration);
		virtual void handleEffect(const float elapsed);
		virtual void handleEffect(const Skill &skill);
		virtual const bool & isExist() const;
		virtual const sf::Time & getDuration() const;
		virtual const Normal & getNormalEffect() const;
		virtual ~Effect();

	protected:
		Effect();

	private:
		sf::Time duration;
		Normal currentNormalE;
		Attribute currentAttributeE;
		bool exist;
	};
	typedef Effect::Normal NormalE;
	typedef Effect::Attribute AttributeE;
}

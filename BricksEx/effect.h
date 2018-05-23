#pragma once
#include <SFML/System/Time.hpp>

namespace game {
	class Skill;

	class Effect {
	public:
		enum class Normal {
			None,
			Fragile,
			Gravitational,
			Hugify,
			Invincible,
			Invisible,
			Invulnerable,
			Magnetic,
			Penetrate,
			SlowDown,
			SpeedUp,
			Sturdy,
		};
		// for stable version release
		enum class Attribute {
			None,
			Blind,				// darkness
			Combustion,			// flame
			Dazzling,			// light
			Frozen,				// ice
			Paralysis,			// thunder
			Poisoning,			// poison
		};
		explicit Effect(const Normal effect, const bool isSkill, const sf::Time duration);
		virtual void handleEffect(const float elapsed);
		virtual const bool & isExist() const;
		virtual const sf::Time & getDuration() const;
		virtual const Normal & getNormalEffect() const;
		virtual ~Effect();

	protected:
		Effect();
		virtual void handleEffect(Skill &);

	private:
		sf::Time duration;
		Normal currentNormalE;
		Attribute currentAttributeE;
		bool exist;
	};
	typedef Effect::Normal NormalE;
	typedef Effect::Attribute AttributeE;
}

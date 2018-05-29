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
			NoCD,
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
		// one effect, one normal/attribute effect
		explicit Effect(const Normal effect, const sf::Time duration);
		explicit Effect(const Normal effect, const Skill * skill);
		virtual void handleEffect(const float elapsed);
		virtual const bool & isExist() const;
		virtual const sf::Time & getDuration() const;
		virtual const Normal & getNormalEffect() const;
		virtual ~Effect();

	protected:
		Effect();
		virtual void handleEffect(Skill *);

	private:
		sf::Time duration;
		Normal normalEffect;
		Attribute attributeEffect;
		bool exist;
		bool isBelongToSkill;
	};
	typedef Effect::Normal NormalEffect;
	typedef Effect::Attribute AttributeEffect;
}

#pragma once
#include "../system.h"
#include <SFML/System/Time.hpp>

namespace game {
	class EffectSystem : public System {
	public:
		// one effect, one normal/attribute effect
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
		virtual void handleEffect();

		virtual const bool & isExist() const;
		virtual const sf::Time & getDuration() const;
		virtual ~EffectSystem();

	protected:
		EffectSystem(const sf::Time &duration, const bool belongToSkill, const bool enable = true);
		virtual void setEnable(const bool) override;
		sf::Time duration;
		sf::Time elapsedTime;

	private:
		bool belongToSkill;
		// used to checkout in particular mode
		bool exist;
	};
	typedef EffectSystem::Normal Normal;
	typedef EffectSystem::Attribute Attribute;
}
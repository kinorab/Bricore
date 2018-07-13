#pragma once

namespace game {
	class Effect;
	class Attribute;
	template<typename T> class EffectKind;

	template<> class EffectKind<Effect> {
	public:
		enum Kind {
			None,
			Gravitational,		// let target be gravitational(some already have gravity things can be turn to target's gravity)
			Invisible,			// let target be invisible
			Invulnerable,		// let target be invulnerable
			Magnetic,			// let target be magnetic
			Fragile,
			SlowDown,
			Hugify,
			Invincible,
			NoCoolDown,
			Penetrability,
			SpeedUp,
			Sturdy,
		};
	};
	template<> class EffectKind<Attribute> {
	protected:
		// for stable version release
		enum AttributeEffect {
			None,
			Combustion,			// flame
			Frozen,				// ice
			Paralysis,			// thunder
			Blind,				// darkness
			Dazzling,			// light
			Poisoning,			// poison
		};
	};
}
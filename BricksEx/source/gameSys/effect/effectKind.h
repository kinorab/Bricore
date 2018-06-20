#pragma once

namespace game {
	class Effect;
	class Attribute;
	template<typename T> class EffectKind;

	template<> class EffectKind<Effect> {
	public:
		enum Kind {
			None,
			Gravitational,
			Invisible,
			Invulnerable,
			Magnetic,
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
		enum Effect {
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
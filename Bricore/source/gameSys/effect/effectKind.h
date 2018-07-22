#pragma once

namespace game {
	class Effect;
	class Arena;
	class Attribute;
	template<typename T> class EffectKind;

	template<> class EffectKind<Effect> {
	public:
		enum Kind {
			Invisible,			// let target be invisible
			Invulnerable,		// let target be invulnerable
			Sturdy,
			Fragile,
			SpeedUp,
			SlowDown,
			Hugify,
			Shrink,
			Poison
		};
	};
	template<> class EffectKind<Arena> {
	public:
		enum class ArenaEffect {
			Poison
		};
	};
	template<> class EffectKind<Attribute> {
	protected:
		// for stable version release
		enum class AttributeEffect {
			None,
			Combustion,			// flame
			Frozen,				// ice
			Paralysis,			// thunder
			Blind,				// darkness
			Dazzling,			// light
		};
	};
}
#pragma once
#include "effectKind.h"

namespace game {
	class Attribute	
		: public EffectKind<Attribute> {
	public:
		// for stable version release
		enum Kind {
			None,
			Flame,
			Ice,
			Thunder, 
			Darkness,
			Light,
			Poison,
		};
		explicit Attribute(const Kind element);
		const Kind it;
		const Effect effect;
		Attribute(const Attribute &) = delete;
		Attribute &operator =(const Attribute &) = delete;
		virtual ~Attribute();
	};
}
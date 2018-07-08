#pragma once
#include "effectKind.h"

namespace game {
	class Effect :
		public EffectKind<Effect> {
	public:
		explicit Effect(const Kind effect) noexcept;
		const Kind it;
		Effect(const Effect &) = delete;
		Effect &operator =(const Effect &) = delete;
		virtual ~Effect();
	};
}
#pragma once
#include "itemKind.h"

namespace item {
	class Core :
		public ItemKind<Core> {
	public:
		explicit Core(const Kind kind) noexcept;
		virtual ~Core();
		const Kind type;
		Core(const Core &) = delete;
		Core & operator =(const Core &) = delete;
	};
}
#pragma once
#include "itemKind.h"

namespace item {
	class Chip :
		public ItemKind<Chip> {
	public:
		explicit Chip(const Kind kind) noexcept;
		virtual ~Chip();
		const Kind chip;
		Chip(const Chip &) = delete;
		Chip & operator =(const Chip &) = delete;
	};
}
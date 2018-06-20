#pragma once
#include "barSystem.h"

namespace game {
	class Boss;

	class RageBar : 
		public BarSystem
		, public sf::Drawable
		, public sf::Transformable {
		friend class Boss;
	public:
		RageBar(const size_t maxCount, const bool debut = false, const bool numberVisible = false);
		virtual void handleBar(const sf::Event * const event) override;
		virtual ~RageBar();
	private:
		virtual void clearBar();
	};
}
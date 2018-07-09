#pragma once
#include "barSystem.h"

namespace game {
	class RageBar : 
		public BarSystem
		, public sf::Drawable
		, public sf::Transformable {
	public:
		explicit RageBar(const size_t maxCount, const bool appear, const bool exist, const bool numberVisible = false);
		virtual void handleBar(const sf::Event * const event) override;
		virtual ~RageBar();
	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
	};
}
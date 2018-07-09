#pragma once
#include "barSystem.h"

namespace game {
	class LifeBar :
		public BarSystem
		, public sf::Drawable
		, public sf::Transformable {
	public:
		explicit LifeBar(const size_t maxCount, const bool appear, const bool exist, const bool numberVisible = false);
		virtual void handleBar(const sf::Event * const event) override;
		virtual ~LifeBar();
	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
	};
}
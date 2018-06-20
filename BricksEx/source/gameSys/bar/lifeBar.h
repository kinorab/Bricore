#pragma once
#include "barSystem.h"

namespace game {
	class SubPlayerSkill;

	class LifeBar :
		public BarSystem
		, public sf::Drawable
		, public sf::Transformable {
		friend class SubPlayerSkill;
	public:
		LifeBar(const size_t maxCount, const bool debut = false, const bool numberVisible = false);
		virtual void handleBar(const sf::Event * const event) override;
		virtual ~LifeBar();
	};
}
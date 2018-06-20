#pragma once
#include "barSystem.h"

namespace game {
	class PlayerSkill;
	class SubPlayerSkill;

	class EnergeBar :
		public BarSystem
		, public sf::Drawable
		, public sf::Transformable {
		friend class PlayerSkill;
		friend class SubPlayerSkill;
	public:
		EnergeBar(const size_t maxCount, const bool debut = false, const bool numberVisible = false);
		virtual void handleBar(const sf::Event * const event) override;
		virtual ~EnergeBar();
	private:
		virtual void clearBar();
	};
}


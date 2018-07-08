#pragma once
#include "../system.h"
#include <SFML/System/Time.hpp>
#include <memory>

namespace game {
	class EffectSystem : public System {
	public:
		bool isExist() const;
		const sf::Time & getDuration() const;
		bool isBelongToSkill() const;
		virtual ~EffectSystem();

	protected:
		explicit EffectSystem(const sf::Time &duration, const bool belongToSkill, const bool enable, const bool exist);
		void setEnable(const bool enable);
		sf::Time duration;
		sf::Time elapsedTime;

	private:
		bool bBelongToSkill;
		// used to checkout in particular mode
		bool bExist;
	};
}
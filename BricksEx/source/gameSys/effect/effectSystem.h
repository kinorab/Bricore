#pragma once
#include "../system.h"
#include <SFML/System/Time.hpp>

namespace game {
	class EffectSystem : public System {
	public:
		virtual bool isExist() const;
		virtual const sf::Time & getDuration() const;
		virtual bool isBelongToSkill() const;
		virtual ~EffectSystem();

	protected:
		explicit EffectSystem(const sf::Time &duration, const bool belongToSkill, const bool enable);
		virtual void setEnable(const bool) override;
		sf::Time duration;
		sf::Time elapsedTime;

	private:
		bool belongToSkill;
		// used to checkout in particular mode
		bool exist;
	};
}
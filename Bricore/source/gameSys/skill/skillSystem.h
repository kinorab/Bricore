#pragma once
#include "../system.h"
#include "../effect/effect.h"
#include "../attribute/attribute.h"
#include "../../event/mouse/mouseEvent.h"
#include "../../event/keyboard/keyEvent.h"
#include "../../event/game/gameEvent.h"
#include <memory>
#include <vector>

namespace sf {
	class Event;
}

namespace game {
	class Effect;
	class Attribute;

	class SkillSystem : 
		public System {
	public:
		// apply handler to insert, addListener
		virtual void initialize() = 0;
		virtual void update() = 0;
		void setExist(const bool exist);
		void upgradeSkill(const size_t number);
		void extendMaxLevel(const size_t number);
		void setOwnToPlayer(const bool giveOwn);

		bool isExist() const;
		bool isLocked() const;
		bool isSilenced() const;
		const sf::Time & getDuration() const;
		size_t getLevel() const;
		size_t getmaxLevel() const;
		virtual ~SkillSystem();

	protected:
		enum Status {
			// not own the skill yet, Gain ways:
			// (sub)player: Need to destroy the boss special part, some can buy on store
			// ball: Need to buy on store
			None,
			Selected,		// selected skill in current level
			UnSelected		// unselected skill in current level
		};
		explicit SkillSystem(const sf::Time &duration, const bool exist);
		bool selectOn();
		bool selectOff();
		void useSkill();
		bool elapsed();
		void exhausted();
		
		size_t uLevel;
		size_t uMaxLevel;
		// cannot swap, move to another field
		bool bLocked;
		// cannot use
		bool bSilenced;
		sf::Time duration;
		sf::Time elapsedTime;
		Status status;
		std::vector<std::shared_ptr<Effect>> skillEffects;
		std::vector<std::shared_ptr<Attribute>> skillAttributes;

	private:
		void setEnable(const bool enable);
		// In particular mode will use
		bool bExist;
	};
}

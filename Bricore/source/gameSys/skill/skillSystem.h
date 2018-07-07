#pragma once
#include "../system.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
#include <vector>

namespace sf {
	class Event;
}

namespace game {
	class EntireEffect;
	class Attribute;

	class SkillSystem : 
		public System {
	public:
		// interact on level
		virtual void handleSkill(const sf::Event * const event) = 0;
		// interact before entering level
		virtual void handleSelect(const sf::Event * const event) = 0;
		void upgradeSkill(const size_t number);
		void extendMaxLevel(const size_t number);
		void setOwnToPlayer(const bool giveOwn);
		void setAutoUse(const bool autoUse);

		bool isExist() const;
		bool isAutoUse() const;
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
		explicit SkillSystem(const sf::Time &duration, bool autoUse = false, const bool exist = true);
		bool selectOn();
		bool selectOff();
		void useSkill();
		bool elapsed();
		void exhausted();
		
		size_t uLevel;
		size_t uMaxLevel;
		bool bAutoUse;
		// cannot swap, move to another field
		bool bLocked;
		// cannot use
		bool bSilenced;
		sf::Time duration;
		sf::Time elapsedTime;
		Status status;
		std::vector<std::shared_ptr<EntireEffect>> skillEffects;
		std::vector<std::shared_ptr<Attribute>> skillAttributes;

	private:
		void setEnable(const bool enable);
		// used to checkout in particular mode
		bool bExist;
	};
}

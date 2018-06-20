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
		virtual void upgradeSkill(const size_t number);
		virtual void extendMaxLevel(const size_t number);
		virtual void setOwnToPlayer(const bool giveOwn);
		virtual void setAutoUse(const bool autoUse);

		virtual bool isExist() const;
		virtual bool isAutoUse() const;
		virtual const sf::Time & getDuration() const;
		virtual size_t getLevel() const;
		virtual size_t getmaxLevel() const;
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
		virtual bool selectOn();
		virtual bool selectOff();
		virtual void useSkill();
		virtual bool elapsed();
		virtual void exhausted();
		
		sf::Time duration;
		sf::Time elapsedTime;
		size_t level;
		size_t maxLevel;
		std::vector<std::shared_ptr<EntireEffect>> skillEffects;
		std::vector<std::shared_ptr<Attribute>> skillAttributes;
		Status status;
		bool autoUse;
		// cannot swap, move to another field
		bool locked;
		// cannot use
		bool silenced;

	private:
		virtual void setEnable(const bool enable) override;
		// used to checkout in particular mode
		bool exist;
	};
}

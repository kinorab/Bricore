#pragma once
#include "AISystem.h"
#include "../item/core.h"
#include "../attribute/attribute.h"
#include "../../interact/container.h"
#include <memory>
#include <map>

namespace sf {
	class Event;
	class Texture;
	class Sprite;
	class RenderTarget;
	class RenderStates;
}

namespace game {
	class BossSkill;

	class Boss :
		public AISystem
		, public Container {
	public:
		enum Name {
			Punece,
			Felifice,
			Apache
		};
		explicit Boss(const Boss &copy);
		explicit Boss(const Name name, const item::Core::Kind core, const Attribute::Kind attribute
			, std::vector<BossSkill> && skills, const size_t maxSkillOnUsing);
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		void update(const float updateRatio);
		void addBossSkill(BossSkill && bossSkill);
		void extendMaxOnUsing(const size_t number);
		void changeCore(const item::Core::Kind type);
		//void offset(const sf::Vector2f &offset, const sf::Time &moveTime);
		//void moveTo(const sf::Vector2f &coordinate, const sf::Time &moveTime);
		static void setDisplay(const bool isDisplay);

		static bool isDisplay();
		std::string getName() const;
		Attribute::Kind getAttribute() const;
		item::Core::Kind getCore() const;
		size_t getMaxOnUsing() const;
		size_t getPartAmount() const;
		size_t getIntensePartAmount() const;
		size_t getIntensifiedPartAmount() const;
		size_t getWeakPartAmount() const;
		size_t getBrokenPartAmount() const;
		bool isAlive() const;
		bool isDebut() const;
		Boss &operator =(Boss copy);
		virtual ~Boss();

	protected:
		void weakPartBreak(const std::string & weak_partName);
		void weakPartRecover(const std::string & weak_partName);
		void partIntensify(const std::string & intense_partName);
		void partRecover(const std::string & intense_partName);
		void debut();
		struct Part {
			std::shared_ptr<sf::Sprite> context;
		};
		struct IntensePart {
			std::shared_ptr<sf::Sprite> context;
			bool bIntensified = false;
		};
		struct WeakPart {
			std::shared_ptr<sf::Sprite> context;
			bool bBroke = false;
		};
		struct BossContent {
			Name bossName;
			size_t maxOnUsingSkill;
			std::shared_ptr<item::Core> core;
			std::shared_ptr<Attribute> attribute;
			// partName
			std::map<std::string, Part> parts;
			// intense_partName
			std::map<std::string, IntensePart> intenseParts;
			// weak_partName
			std::map<std::string, WeakPart> weakParts;
			std::vector<std::shared_ptr<BossSkill>> skills;
		};

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		// clear and resettle all parts
		void resettleParts();
		// partName
		// intense_partName
		// intense_partName_intensified
		// weak_partName
		// weak_partName_broke
		static std::multimap<Name, std::string> partFileNames;
		static bool bDisplay;

		bool bMove;
		bool bAlive;
		bool bDebut;
		BossContent boss;
	};
}
#pragma once
#include "AISystem.h"
#include "../item/core.h"
#include "../effect/attribute.h"
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
	class Attribute;

	class Boss :
		public AISystem
		, public Container {
	public:
		explicit Boss(const Boss &copy);
		explicit Boss(const std::string name, const Attribute::Kind &attribute
			, const std::vector<BossSkill> &skills, const size_t maxSkillOnUsing);
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		void loadPartPreviews(const std::vector<std::string> &fileName, const bool isSmooth = false);
		void debut(const item::Core::Kind type);
		void update(const float updateRatio);
		void handle(const sf::Event & event);
		void addBossSkill(BossSkill && bossSkill);
		void extendMaxOnUsing(const size_t number);
		void changeCore(const item::Core::Kind type);
		void offset(const sf::Vector2f &offset, const sf::Time &moveTime);
		void moveTo(const sf::Vector2f &coordinate, const sf::Time &moveTime);
		static void loadCorePreviews(const std::map<item::Core::Kind, std::string> &fileName
			, const bool isSmooth = false);

		Attribute::Kind getAttribute() const;
		item::Core::Kind getBossCore() const;
		const std::string & getBossName() const;
		size_t getMaxOnUsing() const;
		size_t getPartAmount() const;
		size_t getIntensifiedPartAmount() const;
		size_t getWeakPartAmount() const;
		size_t getBrokenPartAmount() const;
		bool isExist() const;
		Boss &operator =(Boss copy);
		virtual ~Boss();

	protected:
		void weakPartBreak(const std::string &weak_partName);
		void weakPartRecover(const std::string &weak_partName);
		void partIntensify(const std::string &partName);
		void partRecover(const std::string &partName);
		struct Part {
			std::shared_ptr<sf::Sprite> context;
			bool bIntensified = false;
		};
		struct WeakPart {
			std::shared_ptr<sf::Sprite> context;
			bool bBroke = false;
		};
		struct BossContent {
			std::string bossName;
			size_t maxOnUsingSkill;
			std::shared_ptr<item::Core> core;
			std::shared_ptr<Attribute> attribute;
			// partName
			std::map<std::string, Part> parts;
			// weak_partName
			std::map<std::string, WeakPart> weakParts;
			std::vector<std::shared_ptr<BossSkill>> skills;
		};

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		static std::map<item::Core::Kind, std::shared_ptr<sf::Texture>> corePreviews;

		bool bMove;
		bool bExist;
		// partName & partName_intense & weak_partname & weak_partName_broke
		std::map<std::string, std::shared_ptr<sf::Texture>> partPreviews;
		BossContent boss;
	};
}
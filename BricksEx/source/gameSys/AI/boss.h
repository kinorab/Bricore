#pragma once
#include "AISystem.h"
#include "../item/core.h"
#include "../effect/attribute.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>
#include <memory>
#include <mutex>
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
		, public sf::Drawable
		, public sf::Transformable {
	public:
		explicit Boss(const std::string name, const Attribute::Kind &attribute
			, const std::vector<BossSkill> &skills, const size_t maxSkillUsing);
		virtual void loadPartPreviews(const std::vector<std::string> &fileName, const bool isSmooth = false);
		virtual void update(const float intervalRate);
		virtual void handle(const sf::Event * const event) override;
		virtual void extendMaxOnUsing(const size_t number);
		virtual void offset(const sf::Vector2f &offset, const sf::Time &moveTime);
		virtual void moveTo(const sf::Vector2f &coordinate, const sf::Time &moveTime);
		static void loadCoreTypePreviews(const std::map<item::Core::Kind, std::string> &fileName, const bool isSmooth = false);

		static size_t getCoreTypeAmount();
		virtual Attribute::Kind getAttribute() const;
		virtual item::Core::Kind getBossCoreType() const;
		virtual const std::string & getBossName() const;
		virtual size_t getMaxOnUsing() const;
		virtual size_t getPartAmount() const;
		virtual size_t getIntensifiedPartAmount() const;
		virtual size_t getWeakPartAmount() const;
		virtual size_t getBrokenPartAmount() const;
		virtual bool isExist() const;
		virtual ~Boss();
		explicit Boss(const Boss &copy);
		Boss &operator =(Boss copy);

	protected:
		virtual void debut(const item::Core::Kind type);
		virtual void changeCoreType(const item::Core::Kind type);
		virtual void weakPartBreak(const std::string &weak_partName);
		virtual void weakPartRecover(const std::string &weak_partName);
		virtual void partIntensify(const std::string &partName);
		virtual void partRecover(const std::string &partName);
		struct Part {
			std::shared_ptr<sf::Sprite> context;
			bool intensified;
		};
		struct WeakPart {
			std::shared_ptr<sf::Sprite> context;
			bool broke;
		};
		struct CoreType {
			std::string bossName;
			std::shared_ptr<sf::Sprite> context;
			std::shared_ptr<item::Core> core;
		};

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		static std::map<item::Core::Kind, std::shared_ptr<sf::Texture>> coreTypePreviews;
		// partName & partName_intense & weak_partname & weak_partName_broke
		std::map<std::string, std::shared_ptr<sf::Texture>> partPreviews;
		struct Content {
			size_t maxOnUsing;
			std::shared_ptr<Attribute> attribute;
			std::vector<std::shared_ptr<BossSkill>> skills;
			// partName
			std::map<std::string, Part> parts;
			// weak_partName
			std::map<std::string, WeakPart> weakParts;
		};
		// CoreType / Content
		std::pair<CoreType, Content> boss;
		bool moving;
		bool exist;
	};
}
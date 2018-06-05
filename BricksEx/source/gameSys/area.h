#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <vector>
#include <map>

namespace game {
	class NormalEffect;

	class Area {
	public:
		enum class Item {
			AttackCore,
			BallLifeCore,
			DefendCore,
			HealCore,
			SkillCDCore,
			ReviveCore
		};
		virtual void update();
		virtual bool isAOEempty(const std::string name) const;
		virtual ~Area();
	private:
		struct AreaItem {
			std::vector<std::shared_ptr<NormalEffect>> effects;
			std::shared_ptr<sf::Texture> lightPower;
			std::shared_ptr<sf::Texture> context;
			std::shared_ptr<sf::Sprite> core;
		};
		std::map<Item, AreaItem> areaItems;
		std::map<std::string, std::vector<std::shared_ptr<NormalEffect>>> AOEs;
	};
}
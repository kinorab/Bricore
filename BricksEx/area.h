#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <vector>
#include <map>

namespace game {
	class Effect;

	class Area {
	public:
		enum class Item {
			BallLifeCore,
			HealCore,
			SkillCDCore,
			ReviveCore
		};
		virtual void update();
		virtual bool isAOEempty(const std::string name) const;
		virtual ~Area();
	private:
		struct AreaItem {
			Item itemName;
			std::vector<Effect> effects;
			sf::Texture lightPower;
			sf::Texture context;
			sf::Sprite core;
		};
		std::map<std::string, AreaItem> areaItems;
		std::map<std::string, std::vector<Effect>> AOEs;
	};
}
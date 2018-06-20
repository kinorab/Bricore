#pragma once
#include "../system.h"
#include "../item/enerma.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
#include <vector>
#include <map>

namespace sf {
	class Sprite;
	class Texture;
	class Event;
	class RenderTarget;
	class RenderStates;
}

namespace game {
	class EntireEffect;
	class Attribute;

	class Area : 
		public System
		, public sf::Drawable
		, public sf::Transformable {
	public:
		Area();
		virtual void update(const sf::Event * const event);
		static void loadEnermaPreviews(const std::map<item::Enerma::Kind, std::string> &fileName, const bool isSmooth = false);
		static void loadLightPreviews(const std::vector<std::string> &fileName, const bool isSmooth = false);
		static void cleanUpLightPowerCache();
		virtual ~Area();

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		struct Content {
			std::vector<std::shared_ptr<EntireEffect>> effects;
			std::shared_ptr<sf::Sprite> lightPower;
			std::shared_ptr<sf::Sprite> context;
			std::shared_ptr<item::Enerma> content;
		};
		std::map<item::Enerma::Kind, Content> enermas;
		std::map<std::string, std::vector<std::shared_ptr<Attribute>>> AOEs;
		static std::map<item::Enerma::Kind, std::shared_ptr<sf::Texture>> enermaPreviews;
		static std::map<std::string, std::shared_ptr<sf::Texture>> lightPreviews;
	};
}
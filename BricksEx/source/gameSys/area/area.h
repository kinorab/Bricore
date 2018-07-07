#pragma once
#include "../../template/singleton.h"
#include <SFML/System/Vector2.hpp>
#include <memory>

namespace sf {
	class RectangleShape;
	class Color;
}

namespace game {
	class Area :
		public Singleton<Area> {
		friend class Singleton<Area>;
	public:
		enum Label {
			Player,
			Obstacle,
			Wall
		};
		// area's position
		void settleArea(const Label name, const sf::Vector2f &position);
		// area's height
		void settleArea(const Label name, const float height);
		// area's position and height
		void settleArea(const Label name, const sf::Vector2f &position, const float height);
		// outline color
		void setAreaOutline(const Label name, const sf::Color &color);
		// outline thickness
		void setAreaOutline(const Label name, const float thickness);
		// outline color and thickness
		void setAreaOutline(const Label name, const float thickness, const sf::Color &color);
		const sf::RectangleShape & getArea(const Label name) const;

	protected:
		Area();

	private:
		std::unique_ptr<sf::RectangleShape> playerArea;
		std::unique_ptr<sf::RectangleShape> obstacleArea;
		std::unique_ptr<sf::RectangleShape> wallArea;
	};
}
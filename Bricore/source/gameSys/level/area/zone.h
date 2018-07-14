#pragma once
#include "../../../template/singleton.h"
#include <SFML/System/Vector2.hpp>
#include <memory>

namespace sf {
	class RectangleShape;
	class Color;
}

namespace game {
	class Zone :
		public Singleton<Zone> {
		friend class Singleton<Zone>;
	public:
		enum Label {
			Player,
			Obstacle,
			Wall
		};
		// area's position
		void settleZone(const Label name, const sf::Vector2f &position);
		// area's height
		void settleZone(const Label name, const float height);
		// area's position and height
		void settleZone(const Label name, const sf::Vector2f &position, const float height);
		// outline color
		void setZoneOutline(const Label name, const sf::Color &color);
		// outline thickness
		void setZoneOutline(const Label name, const float thickness);
		// outline color and thickness
		void setZoneOutline(const Label name, const float thickness, const sf::Color &color);
		const sf::RectangleShape & getZone(const Label name) const;
		virtual ~Zone();

	protected:
		Zone() noexcept;

	private:
		std::unique_ptr<sf::RectangleShape> playerZone;
		std::unique_ptr<sf::RectangleShape> obstacleZone;
		std::unique_ptr<sf::RectangleShape> wallZone;
	};
}
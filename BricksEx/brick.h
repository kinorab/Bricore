#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <map>
#include "diagonalPoint.h"

namespace item {
	class Brick :
		public sf::Drawable {

	public:

		Brick(const size_t rowCount, const float width, const float height
			, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f, const float whiteSpaceY = 0.0f);

		static void update();
		static void loadImage(const std::string fileName);
		static void deleteImage(const std::string fileName);
		static void displayImage(const std::string fileName);
		static void setBrickColor(const sf::Color&);
		static void setFrameColor(const sf::Color&);
		static void setSideLength(const sf::Vector2f &sideLength);
		static void setSideLength(const float width, const float height);
		static void setInterval(const sf::Vector2f &interval);
		static void setInterval(const float x, const float y);
		static void setFrameSize(const float frame);

		static void reset(const size_t rowCount, const float width, const float height
			, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f, const float whiteSpaceY = 0.0f);
		static void reset(const size_t rowCount);

		static const size_t getBricksSize();
		static const sf::Vector2f & getSideLength();
		static const sf::Vector2f & getInterval();
		static const float getFrameSize();
		static const sys::DPointf getDP(const size_t number);
		static const sys::DPointf getBrickAreaDP();

	private:

		static void settlePlace();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

		static sf::RectangleShape bricksArea;
		static std::vector <std::unique_ptr<sf::RectangleShape>> bricks;
		static std::map <std::string, sf::Texture *> levelImage;
		// bricks on every row
		static size_t amount;
		static size_t rowCount;
		static float frame;
		static sf::Vector2f interval;
		static sf::Vector2f sideLength;
		static sf::Vector2f whiteSpace;
		static bool changeEntity;
	};
}
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <map>
#include "diagonalPoint.h"

namespace item {
	class Ball;

	class Brick :
		public sf::Drawable {
	public:
		Brick();
		explicit Brick(const Brick &copy);
		virtual void update(Ball &ball);
		virtual void preUpdate(Ball &ball, const float intervalTime);
		virtual void loadImage(const std::string fileName);
		virtual void deleteImage(const std::string fileName);
		virtual void displayImage(const std::string fileName);
		virtual void setBrickColor(const sf::Color&);
		virtual void setFrameColor(const sf::Color&);
		virtual void setSideLength(const sf::Vector2f &sideLength);
		virtual void setSideLength(const float width, const float height);
		virtual void setInterval(const sf::Vector2f &interval);
		virtual void setInterval(const float x, const float y);
		virtual void setFrameSize(const float frame);

		virtual void reset(const size_t rowCount, const float width, const float height
			, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f, const float whiteSpaceY = 0.0f);
		virtual void reset(const size_t rowCount);

		virtual const size_t getBricksSize() const;
		virtual const sf::Vector2f & getSideLength() const;
		virtual const sf::Vector2f & getInterval() const;
		virtual const float getFrameSize() const;
		virtual const sys::DPointf getDP(const size_t number) const;
		virtual const sf::Color getBricksColor() const;
		virtual Brick & operator =(const Brick &);
		virtual ~Brick();

	private:
		virtual void settlePlace();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

		std::map <std::string, sf::Texture *> levelImage;
		std::vector <std::shared_ptr<sf::RectangleShape>> bricks;
		// bricks on every row
		size_t amount;
		size_t rowCount;
		float frameSize;
		sf::Color bricksColor;
		sf::Color frameColor;
		sf::Vector2f interval;
		sf::Vector2f sideLength;
		sf::Vector2f whiteSpace;
		bool changeEntity;
	};
}
#pragma once

#include "ball.h"

namespace item {
	class Brick :
		public sf::Drawable {

	public:

		Brick(const size_t row, const size_t column, const float width, const float height
			, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f);
		Brick(const size_t rowCount, const float width, const float height
			, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f);

		void loadImage(sf::Texture*);
		void setBrickColor(const sf::Color&);
		void setFrameColor(const sf::Color&);
		void setRowAmount(const int row);
		void setSideLength(const sf::Vector2f &sideLength);
		void setSideLength(const float width, const float height);
		void setInterval(const sf::Vector2f &interval);
		void setInterval(const float x, const float y);
		void setFrameSize(const float frame);
		void enable(item::Ball &ball);

		void reset(const size_t rowCount, const float width, const float height
			, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f);
		void reset(const size_t rowCount);

		void reset(const size_t row, const size_t column, const float width, const float height
			, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f);
		void reset(const size_t row, const size_t column);

		const size_t getAreaSize() const;
		const sf::Vector2f & getSideLength() const;
		const sf::Vector2f & getInterval() const;
		const float getFrameSize() const;

	private:

		void settlePlace();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

		std::vector<sf::RectangleShape> area;
		// bricks on every row
		size_t amount;
		sf::Vector2f interval;
		sf::Vector2f sideLength;
		float frame;
		bool changeEntity;
	};
}
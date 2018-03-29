#pragma once

#include "ball.h"
#include <map>

namespace item {
	class Brick :
		public sf::Drawable {

	public:

		Brick(const size_t row, const size_t column, const float width, const float height
			, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f);
		Brick(const size_t rowCount, const float width, const float height
			, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f);

		void loadImage(const std::string fileName);
		void deleteImage(const std::string fileName);
		void setBrickColor(const sf::Color&);
		void setFrameColor(const sf::Color&);
		void setRowAmount(const int row);
		void setSideLength(const sf::Vector2f &sideLength);
		void setSideLength(const float width, const float height);
		void setInterval(const sf::Vector2f &interval);
		void setInterval(const float x, const float y);
		void setFrameSize(const float frame);
		void update(item::Ball &ball);

		void reset(const size_t rowCount, const float width, const float height
			, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f);
		void reset(const size_t rowCount);

		void reset(const size_t row, const size_t column, const float width, const float height
			, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f);
		void reset(const size_t row, const size_t column);

		const bool isEmpty() const;
		const size_t getAreaSize() const;
		const sf::Vector2f & getSideLength() const;
		const sf::Vector2f & getInterval() const;
		const float getFrameSize() const;

	private:

		void settlePlace();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

		std::vector <std::unique_ptr<sf::RectangleShape>> area;
		std::map <std::string, std::unique_ptr<sf::Texture>> levelImage;
		// bricks on every row
		size_t amount;
		sf::Vector2f interval;
		sf::Vector2f sideLength;
		float frame;
		bool changeEntity;

	};
}
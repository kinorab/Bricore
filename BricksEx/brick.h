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
		static std::shared_ptr<Brick> getInstance();
		static std::shared_ptr<Brick> getPredictInstance();
		static bool resetInstance();
		void update();
		void loadImage(const std::string fileName);
		void deleteImage(const std::string fileName);
		void displayImage(const std::string fileName);
		void setBrickColor(const sf::Color&);
		void setFrameColor(const sf::Color&);
		void setSideLength(const sf::Vector2f &sideLength);
		void setSideLength(const float width, const float height);
		void setInterval(const sf::Vector2f &interval);
		void setInterval(const float x, const float y);
		void setFrameSize(const float frame);

		void reset(const size_t rowCount, const float width, const float height
			, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f, const float whiteSpaceY = 0.0f);
		void reset(const size_t rowCount);

		const size_t getBricksSize() const;
		const sf::Vector2f & getSideLength() const;
		const sf::Vector2f & getInterval() const;
		const float getFrameSize() const;
		const sys::DPointf getDP(const size_t number) const;
		const sys::DPointf getBrickAreaDP() const;

	protected:
		Brick();

	private:
		Brick & operator =(const Brick &);
		static std::shared_ptr<Brick> instance;
		void settlePlace();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

		sf::RectangleShape bricksArea;
		std::vector <std::shared_ptr<sf::RectangleShape>> bricks;
		std::map <std::string, sf::Texture *> levelImage;
		// bricks on every row
		size_t amount;
		size_t rowCount;
		float frame;
		sf::Vector2f interval;
		sf::Vector2f sideLength;
		sf::Vector2f whiteSpace;
		bool changeEntity;
	};
}
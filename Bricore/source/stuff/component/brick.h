#pragma once
#include "../../definition/diagonalPoint.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <memory>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class RectangleShape;
	class Color;
}

namespace item {
	class Globular;

	class Brick :
		public sf::Drawable
		, public sf::Transformable {
	public:
		explicit Brick(const sf::Vector2f & size, const float frameSize = 0);
		explicit Brick(const Brick &copy);
		void update(const float updateRatio);
		void loadTexture(const std::string & fileName);
		void setPosition(const sf::Vector2f &position);
		void setBrickSize(const sf::Vector2f &sideLength);
		void setBrickColor(const sf::Color & color);
		void setFrameSize(const float frame);
		void setFrameColor(const sf::Color & color);

		sys::DPointf getDP() const;
		sf::FloatRect getGlobalBounds() const;
		const sf::Vector2f & getBrickSize() const;
		const sf::Color & getBrickColor() const;
		float getFrameSize() const;
		const sf::Color & getFrameColor() const;
		const sf::Vector2f & getPosition() const;
		Brick & operator =(Brick right);
		virtual ~Brick();

	private:
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

		std::shared_ptr<sf::RectangleShape> brick;
	};
}

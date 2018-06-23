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
		virtual void update(const float updateRatio);
		virtual void loadTexture(const std::string & fileName);
		virtual void setPosition(const sf::Vector2f &position);
		virtual void setBrickSize(const sf::Vector2f &sideLength);
		virtual void setBrickColor(const sf::Color & color);
		virtual void setFrameSize(const float frame);
		virtual void setFrameColor(const sf::Color & color);

		virtual sys::DPointf getDP() const;
		virtual sf::FloatRect getGlobalBounds() const;
		virtual const sf::Vector2f & getBrickSize() const;
		virtual const sf::Color & getBrickColor() const;
		virtual float getFrameSize() const;
		virtual const sf::Color & getFrameColor() const;
		virtual const sf::Vector2f & getPosition() const;
		virtual Brick & operator =(Brick right);
		virtual ~Brick();

	private:
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

		std::shared_ptr<sf::RectangleShape> brick;
	};
}

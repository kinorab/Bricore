#pragma once
#include "../../definition/diagonalPoint.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
#include <map>

namespace sf {
	class Color;
	class VertexArray;
	class RenderTarget;
	class RenderStates;
}

namespace item {
	class Block : 
		public sf::Drawable
		, public sf::Transformable {
	public:
		explicit Block(const sf::Vector2f &position, const sf::Vector2f &size);
		explicit Block(const Block &copy);
		virtual void update(const float updateRatio);
		virtual void loadTexture(const std::string &fileName);
		virtual void setOrigin(const sf::Vector2f & position);
		virtual void setPosition(const sf::Vector2f &position);
		virtual void setVerticeColor(const sf::Color &);
		virtual void setVerticeColor(const sf::Color &, const sf::Color &, const sf::Color &, const sf::Color &);
		virtual void setSize(const sf::Vector2f &size);
		virtual void setSpeed(const float speedX, const float speedY = 0.0f);
		virtual void setSpeed(const sf::Vector2f &speed);
		virtual void resetPosition();

		virtual sys::DPointf getDP() const;
		virtual sf::Vector2u getTextureSize() const;
		virtual const sf::Vector2f & getSize() const;
		virtual const sf::Color & getVerticeColor(const size_t index) const;
		virtual const sf::Vector2f & getOrigin() const;
		virtual const sf::Vector2f & getPosition() const;
		virtual const sf::Vector2f & getInitialPosition() const;
		virtual const sf::Vector2f & getSpeed() const;
		virtual Block & operator =(Block right);
		virtual ~Block();

	protected:
		virtual void setBlockVertice();
		virtual void moveEntity(const float updateRatio);

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

		sf::Vector2f initPosition;
		sf::Vector2f position;
		sf::Vector2f origin;
		sf::Vector2f speed;
		sf::Vector2f size;
		std::shared_ptr<sf::Texture> texture;
		std::shared_ptr<sf::VertexArray> block;
	};
}
#pragma once
#include "../../interact/interactiveObject.h"
#include "../../definition/diagonalPoint.h"
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
		public game::InteractiveObject
		, public std::enable_shared_from_this<Block> {
	public:
		// origin in center
		explicit Block(const sf::Vector2f &position, const sf::Vector2f &size);
		explicit Block(const Block &copy);
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		void update(const float updateRatio);
		void loadTexture(const std::string &fileName);
		void setOrigin(const sf::Vector2f & origin);
		void setPosition(const sf::Vector2f &position);
		void setVerticeColor(const sf::Color &);
		void setVerticeColor(const sf::Color &, const sf::Color &, const sf::Color &, const sf::Color &);
		void setSize(const sf::Vector2f &size);
		void setSpeed(const float speedX, const float speedY = 0.0f);
		void setSpeed(const sf::Vector2f &speed);
		void resetPosition();

		sys::DPointf getDP() const;
		sf::Vector2u getTextureSize() const;
		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;
		sf::Vector2f getPosition() const;
		const sf::Vector2f & getSize() const;
		const sf::Color & getVerticeColor(const size_t index) const;
		const sf::Vector2f & getOrigin() const;
		const sf::Vector2f & getInitialPosition() const;
		const sf::Vector2f & getSpeed() const;
		Block & operator =(Block right);
		virtual ~Block();

	protected:
		void settleBlockVertice();
		void moveEntity(const float updateRatio);

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
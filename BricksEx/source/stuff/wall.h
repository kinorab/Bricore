#pragma once
#include "../definition/diagonalPoint.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
#include <vector>

namespace item {
	class Brick;
}

namespace sf {
	class Color;
}

class Ball;

class Wall :
	public sf::Drawable
	, public sf::Transformable {
public:
	Wall();
	virtual void update(Ball &ball, const float updateRatio);
	virtual void loadTexture(const std::string & fileName);
	virtual void setBricksColor(const sf::Color & color);
	virtual void setFramesColor(const sf::Color & color);
	virtual void setBricksSize(const sf::Vector2f &sideLength);
	virtual void setInterval(const sf::Vector2f &interval);
	virtual void setFrameSize(const float frame);

	virtual void reset(const size_t rowCount, const float width, const float height
		, const sf::Vector2f &interval = sf::Vector2f(0.0f, 0.0f), const float frameSize = 0.0f, const float whiteSpaceY = 0.0f);
	virtual void reset(const size_t rowCount);

	virtual size_t getBrickAmount() const;
	virtual sys::DPointf getDP(const size_t number) const;
	virtual float getFrameSize(const size_t number) const;
	virtual const sf::Vector2f & getBrickSize(const size_t number) const;
	virtual const sf::Color & getBrickColor(const size_t number) const;
	virtual const sf::Vector2f & getInterval() const;
	virtual ~Wall();

protected:
	virtual void settlePlace();

private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

	std::vector<std::shared_ptr<item::Brick>> bricks;
	// bricks on every row
	size_t amount;
	size_t rowCount;
	float frameSize;
	sf::Vector2f sideLength;
	sf::Vector2f interval;
	sf::Vector2f whiteSpace;
	bool changeEntity;
};

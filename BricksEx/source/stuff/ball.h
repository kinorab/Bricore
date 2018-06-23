#pragma once
#include "../definition/diagonalPoint.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <memory>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Color;
}

namespace item {
	class MainBall;
	class ShadowBall;
	class Globular;
	class Block;
	class Brick;
}

class Ball :
	public sf::Drawable
	, public sf::Transformable {

public:
	Ball();
	virtual void update(const sys::DPointf &playerDP, const float playerSpeed, const float updateRatio);
	virtual void initializeBall();
	virtual void followPlayer(const sf::Vector2f &pos);
	// return the balls of entered obstacleArea
	virtual std::vector<std::shared_ptr<item::Globular>> enteredObstacleArea() const;
	// return the balls of entered wallArea
	virtual std::vector<std::shared_ptr<item::Globular>> enteredWallArea() const;
	virtual void ballDivided(const size_t numbers);

	virtual float getMainBallRadius() const;
	virtual size_t getBallsAmount() const;
	virtual const sf::Vector2f & getMainBallPosition() const;
	virtual ~Ball();

protected:
	virtual void ballsCollision(const size_t);

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

	bool multiple;
	bool collision;
	std::shared_ptr<item::MainBall> mainBall;
	std::vector<std::shared_ptr<item::ShadowBall>> shadowBalls;
};

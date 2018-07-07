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
	void update(const sys::DPointf &playerDP, const float playerSpeed, const float updateRatio);
	void initializeBall();
	void followPlayer(const sf::Vector2f &pos);
	// return the balls of entered obstacleArea
	std::vector<std::shared_ptr<item::Globular>> enteredObstacleArea() const;
	// return the balls of entered wallArea
	std::vector<std::shared_ptr<item::Globular>> enteredWallArea() const;
	void ballDivided(const size_t numbers);

	float getMainBallRadius() const;
	size_t getBallsAmount() const;
	const sf::Vector2f & getMainBallPosition() const;
	virtual ~Ball();

protected:
	void ballsCollision(const size_t);

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

	bool bMultiple;
	bool bCollision;
	std::shared_ptr<item::MainBall> mainBall;
	std::vector<std::shared_ptr<item::ShadowBall>> shadowBalls;
};

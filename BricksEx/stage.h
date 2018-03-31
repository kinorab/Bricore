#pragma once

#include "ball.h"
#include "brick.h"
#include "container.h"
#include "define.h"
#include "ellipse.h"
#include "hud.h"
#include "particleSystem.h"
#include "obstacle.h"
#include "UIFactory.h"

class Stage :
	public Container {
public:
	Stage();
	virtual ~Stage();
	virtual void update(float updateSpan, sf::Vector2f mousePosition);
private:
	std::shared_ptr<sf::RectangleShape> background;
	std::shared_ptr<item::Ball> ball;
	float blockLength;
	std::shared_ptr<item::Brick> bricks;
	std::shared_ptr<HUD> hud;
	float incre1;
	std::shared_ptr<ParticleSystem> mouseLight;
	std::shared_ptr<Obstacle> obstacles;
	std::shared_ptr<Player> player;
};

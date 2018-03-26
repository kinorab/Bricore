#pragma once

#include "audio.h"
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
	static float blockLength;
	static float incre1;
	explicit Stage(sf::RenderWindow & window);
	virtual ~Stage();
	virtual void update(float updateSpan, sf::Vector2i mousePosition);
private:
	std::shared_ptr<item::Ball> ball;
	std::shared_ptr<item::Brick> bricks;
	std::shared_ptr<HUD> hud;
	std::shared_ptr<ParticleSystem> mouseLight;
	std::shared_ptr<Obstacle> obstacles;
	std::shared_ptr<Player> player;
	sf::RenderWindow & window;
};
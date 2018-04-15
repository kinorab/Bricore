#pragma once

#include "ball.h"
#include "player.h"
#include "brick.h"
#include "container.h"
#include "define.h"
#include "ellipse.h"
#include "hud.h"
#include "particleSystem.h"
#include "obstacle.h"

class Stage
	: public game::Container {
public:
	Stage();
	virtual ~Stage();
	virtual void update(float updateSpan, sf::Vector2f mousePosition);
private:
	static float blockLength;
	static float incre1;
	static std::shared_ptr<item::Ball> ball;
	static std::shared_ptr<item::Brick> bricks;
	static std::shared_ptr<HUD> hud;
	static std::shared_ptr<ParticleSystem> mouseLight;
	static std::shared_ptr<Obstacle> obstacles;
	static std::shared_ptr<Player> player;
	virtual void onMouseEntered(game::Event * event);
	virtual void onMouseLeft(game::Event * event);
	virtual void onMousePressed(game::Event * event);
};

#pragma once
#include "container.h"

namespace item {
	class Ball;
	class Brick;
}
class HUD;
class ParticleSystem;
class Obstacle;
class Player;

class Stage
	: public game::Container {
public:
	void run();
	virtual ~Stage();
	static void update(float updateSpan, sf::Vector2f mousePosition);

private:
	static std::shared_ptr<item::Ball> ball;
	static std::shared_ptr<item::Brick> bricks;
	static std::shared_ptr<HUD> hud;
	static std::shared_ptr<ParticleSystem> mouseLight;
	static std::shared_ptr<Obstacle> obstacles;
	static std::shared_ptr<Player> player;
	virtual void onKeyPressed(game::Event * event);
	virtual void onKeyReleased(game::Event * event);
	virtual void onMouseEntered(game::Event * event);
	virtual void onMouseLeft(game::Event * event);
	virtual void onMouseButtonPressed(game::Event * event);
};

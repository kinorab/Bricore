#pragma once
#include "container.h"

namespace item {
	class Ball;
	class Brick;
}

class Obstacle;
class Player;
class ParticleSystem;
class HUD;

class Stage
	: public game::Container {
public:
	static std::shared_ptr<Stage> getInstance();
	static std::shared_ptr<Stage> getPreInstance();
	static bool resetInstance();
	virtual void update();
	virtual void updateMouseLight(float updateSpan, sf::Vector2f mousePosition);
	virtual ~Stage();

protected:
	Stage();
	virtual void setPredict();
	virtual void predictUpdate();

private:
	virtual void onKeyPressed(game::Event * event);
	virtual void onKeyReleased(game::Event * event);
	virtual void onMouseEntered(game::Event * event);
	virtual void onMouseLeft(game::Event * event);
	virtual void onMouseButtonPressed(game::Event * event);

	static std::shared_ptr<Stage> instance;
	std::shared_ptr<HUD> HUDs;
	std::shared_ptr<ParticleSystem> mouseLight;
	std::shared_ptr<Player> player;
	std::shared_ptr<item::Ball> ball;
	std::shared_ptr<item::Brick> brick;
	std::shared_ptr<Obstacle> obstacle;
	// predict member
	std::shared_ptr<Player> playerPredict;
	std::shared_ptr<item::Ball> ballPredict;
	std::shared_ptr<item::Brick> brickPredict;
	std::shared_ptr<Obstacle> obstaclePredict;
};

#pragma once

#include "interact/container.h"

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
	Stage();
	virtual ~Stage();
	virtual void predictUpdate(const float intervalTime);
	virtual void update(float updateSpan, sf::Vector2f mousePosition);
private:
	static bool instantiated;
	virtual bool getInstantiated() const;
	virtual void setInstantiated(bool value);
	virtual void onKeyPressed(game::Event *);
	virtual void onKeyReleased(game::Event *);
	virtual void onMouseEntered(game::Event *);
	virtual void onMouseLeft(game::Event *);
	virtual void onMouseButtonPressed(game::Event *);

	std::shared_ptr<HUD> hud;
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

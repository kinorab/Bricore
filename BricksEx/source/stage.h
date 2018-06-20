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
	virtual void update(const float updateSpan, const float intervalRate) override;
private:
	static bool instantiated;
	virtual bool getInstantiated() const;
	virtual void setInstantiated(bool value);
	virtual void onKeyPressed(game::Event * event);
	virtual void onKeyReleased(game::Event * event);
	virtual void onMouseEntered(game::Event * event);
	virtual void onMouseLeft(game::Event * event);
	virtual void onMouseMoved(game::Event * event);
	virtual void onMouseButtonPressed(game::Event * event);

	std::shared_ptr<HUD> hud;
	std::shared_ptr<ParticleSystem> mouseLight;
	std::shared_ptr<Player> player;
	std::shared_ptr<item::Ball> ball;
	std::shared_ptr<item::Brick> brick;
	std::shared_ptr<Obstacle> obstacle;
};

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
namespace game {
	class KeyEvent;
	class MouseMoveEvent;
	class MouseButtonEvent;
}

class Stage
	: public game::Container {
public:
	Stage();
	virtual ~Stage();
	virtual void predictUpdate(const float updateSpan);
	virtual void update(const float updateSpan) override;
private:
	static bool instantiated;
	virtual bool getInstantiated() const;
	virtual void setInstantiated(bool value);
	virtual void onKeyPressed(game::KeyEvent & event);
	virtual void onKeyReleased(game::KeyEvent & event);
	virtual void onMouseEntered(game::MouseMoveEvent & event);
	virtual void onMouseLeft(game::MouseMoveEvent & event);
	virtual void onMouseMoved(game::MouseMoveEvent & event);
	virtual void onMouseButtonPressed(game::MouseButtonEvent & event);

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

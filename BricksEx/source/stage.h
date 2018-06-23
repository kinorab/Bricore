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
	class KeyPressedEvent;
	class KeyReleasedEvent;
	class MouseMovedEvent;
	class MouseEnteredEvent;
	class MouseLeftEvent;
	class MousePressedEvent;
	class Stage	: 
		public Container {
	public:
		Stage();
		virtual ~Stage();
		virtual void update(const float updateRatio) override;
	private:
		virtual void onKeyPressed(KeyPressedEvent & event);
		virtual void onKeyReleased(KeyReleasedEvent & event);
		virtual void onMouseEntered(MouseEnteredEvent & event);
		virtual void onMouseLeft(MouseLeftEvent & event);
		virtual void onMouseMoved(MouseMovedEvent & event);
		virtual void onMouseButtonPressed(MousePressedEvent & event);

		std::shared_ptr<HUD> hud;
		std::shared_ptr<ParticleSystem> mouseLight;
		std::shared_ptr<Player> player;
		std::shared_ptr<item::Ball> ball;
		std::shared_ptr<item::Brick> brick;
		std::shared_ptr<Obstacle> obstacle;
	};
}

#pragma once
#include "interact/container.h"
#include "event/game/pausedEvent.h"
#include "event/game/unpausedEvent.h"

class Ball;
class Wall;
class Obstacle;
class Player;
class ParticleSystem;
class HUD;

namespace game {
	class KeyPressedEvent;
	class KeyReleasedEvent;
	class MouseMovedEvent;
	class MousePressedEvent;
	class Stage :
		public Container {
	public:
		Stage();
		virtual ~Stage();
		virtual void update(const float updateRatio) override;
	private:
		virtual void onKeyPressed(KeyPressedEvent & event);
		virtual void onKeyReleased(KeyReleasedEvent & event);
		virtual void onMouseEntered();
		virtual void onMouseLeft();
		virtual void onMouseMoved(MouseMovedEvent & event);
		virtual void onMousePressed(MousePressedEvent & event);

		std::shared_ptr<HUD> hud;
		std::shared_ptr<ParticleSystem> mouseLight;
		std::shared_ptr<Player> player;
		std::shared_ptr<Ball> ball;
		std::shared_ptr<Wall> wall;
		std::shared_ptr<Obstacle> obstacle;
		bool paused = false;
		bool locked = false;
	};
}

#pragma once
#include "interact/container.h"
#include "event/game/pausedEvent.h"
#include "event/game/unpausedEvent.h"

class Ball;
class Wall;
class Obstacle;
class Player;
class SubPlayer;
class HUD;

namespace sf {
	class Event;
}

namespace game {
	class KeyPressedEvent;
	class KeyReleasedEvent;
	class MousePressedEvent;
	class SFMLMouseHandler;
	class SFMLKeyboardHandler;
	class Level;

	class Stage :
		public Container {
	public:
		explicit Stage(const std::shared_ptr<Level> & level);
		void handle(const sf::Event & event);
		virtual ~Stage();

	protected:
		virtual void update(const float updateRatio) override;
		void onKeyPressed(KeyPressedEvent & event);
		void onKeyReleased(KeyReleasedEvent & event);
		// only control on battleArea when no paused
		void onMousePressed(MousePressedEvent & event);
		std::unique_ptr<SFMLMouseHandler> mouseHandler;
		std::unique_ptr<SFMLKeyboardHandler> keyboardHandler;

	private:
		bool bPaused = false;
		std::shared_ptr<Player> player;
		std::shared_ptr<SubPlayer> subPlayer;
		std::shared_ptr<Ball> ball;
		std::shared_ptr<Wall> wall;
		std::shared_ptr<Obstacle> obstacle;
	};
}

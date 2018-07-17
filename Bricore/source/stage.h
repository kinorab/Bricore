#pragma once
#include "interact/container.h"
#include "event/game/gameEvent.h"
#include <SFML/Window/Keyboard.hpp>

namespace sf {
	class RenderWindow;
}

class Ball;
class Wall;
class Obstacle;
class Player;
class SubPlayer;
class HUD;

namespace game {
	class GameHandler;
	class KeyPressedEvent;
	class KeyReleasedEvent;
	class MousePressedEvent;
	class MouseHandler;
	class KeyboardHandler;
	class Level;
	class Root;

	class Stage :
		public Container {
	public:
		explicit Stage(const std::shared_ptr<Level> level, const std::shared_ptr<const Root> root
			, const std::shared_ptr<const sf::RenderWindow> & window);
		void update(const float updateRatio);
		void handle(const sf::Event & event);
		void updateGameStateEvent();
		void resetKey(const sf::Keyboard::Key pause, const sf::Keyboard::Key menu);
		void resetChildrenCopyTarget();
		virtual ~Stage();

	protected:
		void onKeyPressed(KeyPressedEvent & event);
		void onKeyReleased(KeyReleasedEvent & event);
		// only control on battleArea when no paused
		void onMousePressed(MousePressedEvent & event);
		struct StageKey {
			sf::Keyboard::Key pause;
			sf::Keyboard::Key menu;
		};

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

		static bool bInstance;
		StageKey key;
		KeyboardHandler * keyboardHandler;
		MouseHandler * mouseHandler;
		GameHandler * gameHandler;
		GameStateEvent * gameStateEvent;
		GameStateEvent::EventType tempType;
		std::shared_ptr<Player> player;
		std::shared_ptr<SubPlayer> subPlayer;
		std::shared_ptr<Ball> ball;
		std::shared_ptr<Wall> wall;
		std::shared_ptr<Obstacle> obstacle;
		std::shared_ptr<Level> m_level;
		std::shared_ptr<const Root> c_root;
	};
}

#pragma once
#include "interact/container.h"
#include <SFML/Window/Keyboard.hpp>

class Ball;
class Wall;
class Obstacle;
class Player;
class SubPlayer;
class HUD;

namespace game {
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
		explicit Stage(const std::shared_ptr<Level> level, const std::shared_ptr<const game::Root> root);
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		void update(const float updateRatio);
		void handle(const sf::Event & event);
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
		bool bPaused = false;
		StageKey key;
		KeyboardHandler * keyboardHandler;
		MouseHandler * mouseHandler;
		std::shared_ptr<Player> player;
		std::shared_ptr<SubPlayer> subPlayer;
		std::shared_ptr<Ball> ball;
		std::shared_ptr<Wall> wall;
		std::shared_ptr<Obstacle> obstacle;
		std::shared_ptr<game::Level> m_level;
		std::shared_ptr<const Root> c_root;
	};
}

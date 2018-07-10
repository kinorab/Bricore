#pragma once
#include "interact/container.h"
#include "event/game/pausedEvent.h"
#include "event/game/unpausedEvent.h"
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
	class SFMLMouseHandler;
	class SFMLKeyboardHandler;
	class Level;
	class Root;

	class Stage :
		public Container {
	public:
		explicit Stage(const std::shared_ptr<Level> & level, const std::shared_ptr<const game::Root> root);
		void update(const float updateRatio);
		void handle(const sf::Event & event);
		void resetChildrenCopyTarget();
		void resetKey(const sf::Keyboard::Key pause, const sf::Keyboard::Key menu);
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
		std::shared_ptr<Player> player;
		std::shared_ptr<SubPlayer> subPlayer;
		std::shared_ptr<Ball> ball;
		std::shared_ptr<Wall> wall;
		std::shared_ptr<Obstacle> obstacle;
		std::shared_ptr<game::Level> m_level;
		std::shared_ptr<const Root> c_root;
	};
}

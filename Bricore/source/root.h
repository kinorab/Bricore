#pragma once
#include "interact/container.h"

class ParticleSystem;
class HUD;

namespace sf {
	class Event;
	class RenderWindow;
}

class Graphics;

namespace game {
	class MouseMovedEvent;
	class MousePressedEvent;
	class KeyPressedEvent;
	class KeyboardHandler;
	class MouseHandler;
	class Root :
		public Container {
	public:
		explicit Root(const std::shared_ptr<Graphics> graph, const std::shared_ptr<const sf::RenderWindow> & window);
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		void update(const float updateRatio);
		void handle(const sf::Event & event);
		virtual ~Root();

	protected:
		void onMouseEntered();
		void onMouseLeft();
		void onMouseMoved(MouseMovedEvent & event);
		void onMousePressed(MousePressedEvent & event);
		void onKeyPressed(KeyPressedEvent & event);
		void onWindowClosed();

	private:
		static bool bInstance;
		KeyboardHandler * keyboardHandler;
		MouseHandler * mouseHandler;
		std::shared_ptr<HUD> hud;
		std::shared_ptr<ParticleSystem> mouseLight;
		std::shared_ptr<Graphics> m_graph;
	};
}
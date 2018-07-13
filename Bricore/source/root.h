#pragma once
#include "interact/container.h"

class ParticleSystem;
class HUD;

namespace sf {
	class Event;
}

namespace game {
	class MouseMovedEvent;
	class MousePressedEvent;
	class KeyPressedEvent;
	class KeyboardHandler;
	class MouseHandler;
	class Root :
		public Container {
	public:
		Root();
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

	private:
		static bool bInstance;
		KeyboardHandler * keyboardHandler;
		MouseHandler * mouseHandler;
		std::shared_ptr<HUD> hud;
		std::shared_ptr<ParticleSystem> mouseLight;
	};
}
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
	class SFMLMouseHandler;
	class SFMLKeyboardHandler;

	class Root :
		public Container {
	public:
		Root();
		virtual ~Root();

	protected:
		virtual void update(const float updateRatio) override;
		virtual void handle(const sf::Event & event) override;
		void onMouseEntered();
		void onMouseLeft();
		void onMouseMoved(MouseMovedEvent & event);
		void onMousePressed(MousePressedEvent & event);
		void onKeyPressed(KeyPressedEvent & event);
		std::unique_ptr<SFMLMouseHandler> mouseHandler;
		std::unique_ptr<SFMLKeyboardHandler> keyboardHandler;

	private:
		static bool bInstance;
		std::shared_ptr<HUD> hud;
		std::shared_ptr<ParticleSystem> mouseLight;
	};
}
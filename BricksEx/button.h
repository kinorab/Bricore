#pragma once

#include "UIComponent.h"

namespace game {
	class Button
		: public UIComponent {
	public:
		Button();
		void setCaption(std::string caption);
		std::string getCaption();
	private:
		enum class ButtonState {
			UP,
			OVER,
			DOWN
		};
		sf::Font font;
		sf::Sprite spriteUp;
		sf::Sprite spriteOver;
		sf::Sprite spriteDown;
		sf::FloatRect hitArea;
		sf::Sprite * currentSprite;
		std::shared_ptr<sf::Text> text;
		ButtonState currentState;
		void setCurrentState(ButtonState state);
		ButtonState getCurrentState();
	};
}
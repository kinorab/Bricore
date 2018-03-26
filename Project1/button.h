#pragma once

#include "UIComponent.h"

class Button :
	public UIComponent {
public:
	Button();
	void checkClick(sf::Vector2f mousePos);
	void setCaption(std::string caption);
	std::string getCaption();
private:
	enum class ButtonState {
		UP,
		OVER,
		DOWN
	};
	sf::Sprite spriteUp;
	sf::Sprite spriteOver;
	sf::Sprite spriteDown;
	sf::FloatRect hitArea;
	sf::Sprite * currentSprite;
	sf::Text text;
	ButtonState currentState;
	void setCurrentState(ButtonState state);
	ButtonState getCurrentState();
};

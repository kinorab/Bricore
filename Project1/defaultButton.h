#pragma once

#include "button.h"

enum class ButtonState {
	UP,
	OVER,
	DOWN
};

class DefaultButton :
	public Button {
public:
	DefaultButton();
	void checkClick(sf::Vector2f mousePos);
	void setCaption(std::string caption);
	std::string getCaption();

private:
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
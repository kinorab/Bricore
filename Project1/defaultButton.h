#pragma once

#include "button.h"
#include "sprite.h"
#include "defaultContainer.h"

enum class ButtonState {
	UP,
	OVER,
	DOWN
};

class DefaultButton :
	public virtual Button,
	public virtual DefaultContainer {
public:
	DefaultButton();
	void checkClick(sf::Vector2f mousePos);
	void setCaption(std::string caption);
	std::string getCaption();
private:
	Sprite spriteUp;
	sf::Sprite spriteOver;
	sf::Sprite spriteDown;
	sf::FloatRect hitArea;
	sf::Sprite * currentSprite;
	sf::Text text;
	ButtonState currentState;
	void setCurrentState(ButtonState state);
	ButtonState getCurrentState();
};
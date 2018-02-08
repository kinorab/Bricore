#pragma once

#include "button.h"

enum class ButtonState {
	UP,
	OVER,
	DOWN
};

class DefaultButton : public Button {
public:
	DefaultButton(const sf::Texture & up, const sf::Texture & over, const sf::Texture & down, sf::FloatRect hitArea, std::string caption, sf::Vector2f location);
	virtual void checkClick(sf::Vector2f mousePos);
	virtual void setCaption(std::string caption);
	virtual std::string getCaption();

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
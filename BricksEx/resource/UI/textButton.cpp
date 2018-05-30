#include "textButton.h"
#include "../definition/utility.h"

namespace game {
	TextButton::TextButton()
		:text(new sf::Text()) {
		font.loadFromFile("arial.ttf");
		text->setFont(font);
		/*
		spriteUp.setTexture(up);
		spriteOver.setTexture(over);
		spriteDown.setTexture(down);
		currentSprite = &spriteUp;
		spriteUp.setPosition(location);
		spriteOver.setPosition(location);
		spriteDown.setPosition(location);

		setCaption(caption);
		text.setPosition(location.x + 3, location.y + 3);
		text.setCharacterSize(14);
		*/
		addChild({ text });
	}

	TextButton::~TextButton() {
	}

	void TextButton::setCurrentState(ButtonState state) {
		currentState = state;
		if (currentState == ButtonState::UP) {
			currentSprite = &spriteUp;
		}
		else if (currentState == ButtonState::OVER) {
			currentSprite = &spriteOver;
		}
		else if (currentState == ButtonState::DOWN) {
			currentSprite = &spriteDown;
		}
	}

	void TextButton::setCaption(std::string caption) {
		text->setString(caption);
	}

	TextButton::ButtonState TextButton::getCurrentState() {
		return currentState;
	}

	std::string TextButton::getCaption() {
		return text->getString();
	}
}
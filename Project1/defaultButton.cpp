#include "defaultButton.h"

using namespace std;
using namespace sf;

DefaultButton::DefaultButton() {
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
}


void DefaultButton::checkClick(Vector2f mousePos) {
	FloatRect mouseBox(mousePos, Vector2f(0.0f, 0.0f));
	if (mouseBox.intersects(currentSprite->getGlobalBounds())) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			setCurrentState(ButtonState::DOWN);
		}
		else {
			setCurrentState(ButtonState::OVER);
		}
	}
	else {
		setCurrentState(ButtonState::UP);
	}
}

void DefaultButton::setCurrentState(ButtonState state) {
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

void DefaultButton::setCaption(string caption) {
	text.setString(caption);
}

ButtonState DefaultButton::getCurrentState() {
	return currentState;
}

string DefaultButton::getCaption() {
	return text.getString();
}

#include "button.h"
#include "UIComponent.h"
#include "define.h"

using namespace std;
using namespace sf;

Button::Button(Texture * up, Texture * over, Texture * down, FloatRect hitArea, string caption, Vector2f location) {
	this->spriteUp.setTexture(*up);
	this->spriteOver.setTexture(*over);
	this->spriteDown.setTexture(*down);
	this->currentSprite = &this->spriteUp;
	this->hitArea = hitArea;
	this->currentState = ButtonState::UP;
	this->spriteUp.setPosition(location);
	this->spriteOver.setPosition(location);
	this->spriteDown.setPosition(location);
	this->setCaption(caption);
	this->text.setPosition(location.x + 3, location.y + 3);
	this->text.setCharacterSize(14);
}

void Button::checkClick(Vector2f mousePos) {
	FloatRect mouseBox(mousePos, Vector2f(0.0f, 0.0f));
	if (mouseBox.intersects(this->currentSprite->getGlobalBounds())) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			this->setCurrentState(ButtonState::DOWN);
		}
		else {
			this->setCurrentState(ButtonState::OVER);
		}
	}
	else {
		this->setCurrentState(ButtonState::UP);
	}
}

void Button::setCurrentState(ButtonState state) {
	this->currentState = state;
	if (this->currentState == ButtonState::UP) {
		this->currentSprite = &this->spriteUp;
	}
	else if (this->currentState == ButtonState::OVER) {
		this->currentSprite = &this->spriteOver;
	}
	else if (this->currentState == ButtonState::DOWN) {
		this->currentSprite = &this->spriteDown;
	}
}

void Button::setCaption(string caption) {
	this->text.setString(caption);
}

bool Button::getCurrentState() {
	return this->currentSprite;
}

string Button::getCaption() {
	return this->text.getString();
}

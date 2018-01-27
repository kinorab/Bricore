#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


enum class ButtonState {
	UP,
	OVER,
	DOWN
};

class Button {
public:
	Button(const Texture & up, const Texture & over, const Texture & down, FloatRect hitArea, string caption, Vector2f location);
	void checkClick(Vector2f mousePos);
	void setCaption(string caption);
	string getCaption();

private:
	Sprite spriteUp;
	Sprite spriteOver;
	Sprite spriteDown;
	FloatRect hitArea;
	Sprite * currentSprite;
	Text text;
	ButtonState currentState;
	void setCurrentState(ButtonState state);
	ButtonState getCurrentState();
};

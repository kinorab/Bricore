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
	Button(Texture &up, Texture &over, Texture &down, FloatRect hitArea, string caption, Vector2f location);
	void checkClick(Vector2f mousePos);
	void setCurrentState(ButtonState state);
	void setCaption(string caption);
	bool getCurrentState();
	string getCaption();

private:

	static Sprite spriteUp;
	static Sprite spriteOver;
	static Sprite spriteDown;
	FloatRect hitArea;
	Sprite * currentSprite;
	Text text;
	ButtonState currentState;
};

#include "hud.h"
#include "define.h"

using namespace sf;

HUD::HUD() :
	background(new game::RectangleShape(Vector2f(GAME_WIDTH - LEVEL_WIDTH, GAME_HEIGHT))) {
	background->setFillColor(Color::Black);
	addChild({ background });
	setPosition(Vector2f(LEVEL_WIDTH, 0.0f));
}

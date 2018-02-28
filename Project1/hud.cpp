#include "hud.h"
#include "define.h"

using namespace sf;

HUD::HUD() :
	background(new RectangleShape(Vector2f(GAME_WIDTH - STAGE_WIDTH, GAME_HEIGHT))) {
	background->setFillColor(Color::Black);
	addChild({ background });
	setPosition(Vector2f(STAGE_WIDTH, 0.0f));
}

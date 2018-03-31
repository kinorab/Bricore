#include "hud.h"
#include "define.h"

using namespace sf;

HUD::HUD() {
	background.push_back(std::shared_ptr<RectangleShape>(new RectangleShape(Vector2f(GAME_WIDTH - LEVEL_WIDTH, 200.f))));
	background.push_back(std::shared_ptr<RectangleShape>(new RectangleShape(Vector2f(GAME_WIDTH - LEVEL_WIDTH, 300.f))));
	background.push_back(std::shared_ptr<RectangleShape>(new RectangleShape(Vector2f(GAME_WIDTH - LEVEL_WIDTH, 400.f))));
	background.at(0)->setFillColor(Color::Blue);
	background.at(1)->setFillColor(Color::Green);
	background.at(1)->setPosition(Vector2f(0.0f, 200.f));
	background.at(2)->setFillColor(Color::Cyan);
	background.at(2)->setPosition(Vector2f(0.0f, 500.f));
	setPosition(Vector2f(LEVEL_WIDTH, 0.0f));
	addChild({ background.at(0), background.at(1), background.at(2) });
}

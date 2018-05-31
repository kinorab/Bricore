#include "hud.h"
#include "definition/define.h"
#include "gameSys/area.h"
#include <SFML/Graphics.hpp>

HUD::HUD() {
	// interface
	interface.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(LEVEL_WIDTH, LEVEL_HEIGHT))));
	interface.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(GAME_WIDTH - LEVEL_WIDTH, 200.f))));
	interface.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(GAME_WIDTH - LEVEL_WIDTH, 300.f))));
	interface.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(GAME_WIDTH - LEVEL_WIDTH, 400.f))));
	interface.at(0)->setFillColor(sf::Color(180, 180, 180));
	interface.at(1)->setFillColor(sf::Color::Blue);
	interface.at(1)->setPosition({ LEVEL_WIDTH, 0.f });
	interface.at(2)->setFillColor(sf::Color::Green);
	interface.at(2)->setPosition({ LEVEL_WIDTH, 200.f });
	interface.at(3)->setFillColor(sf::Color::Cyan);
	interface.at(3)->setPosition({ LEVEL_WIDTH, 500.f });
	addChild({ interface.at(0), interface.at(1), interface.at(2), interface.at(3) });

	// button
	// addChild({ button });
}

void HUD::setBackgroundColor(const sf::Color &color) {
	interface.at(0)->setFillColor(color);
}

bool HUD::containsPoint(const sf::Vector2f & point) const {
	return Container::containsPoint(point);
}

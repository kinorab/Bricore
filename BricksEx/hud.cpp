#include "hud.h"
#include "define.h"

using namespace sf;

std::vector <std::shared_ptr<sf::RectangleShape>> HUD::interface;
std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> HUD::panel1;
std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> HUD::panel2;
std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> HUD::panel3;

HUD::HUD() {
	interface.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(LEVEL_WIDTH, LEVEL_HEIGHT))));
	interface.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(GAME_WIDTH - LEVEL_WIDTH, 200.f))));
	interface.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(GAME_WIDTH - LEVEL_WIDTH, 300.f))));
	interface.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(GAME_WIDTH - LEVEL_WIDTH, 400.f))));
	interface.at(1)->setFillColor(Color::Blue);
	interface.at(1)->setPosition(Vector2f(LEVEL_WIDTH, 0));
	interface.at(2)->setFillColor(Color::Green);
	interface.at(2)->setPosition(Vector2f(LEVEL_WIDTH, 200.f));
	interface.at(3)->setFillColor(Color::Cyan);
	interface.at(3)->setPosition(Vector2f(LEVEL_WIDTH, 500.f));
	addChild({ interface.at(0), interface.at(1), interface.at(2), interface.at(3) });
}

void HUD::setBackgroundColor(const sf::Color &color) {
	interface.at(0)->setFillColor(color);
}

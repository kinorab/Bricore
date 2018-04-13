#include "hud.h"
#include "define.h"

using namespace sf;

std::vector <std::shared_ptr<sf::RectangleShape>> HUD::interface = []() {
	std::vector <std::shared_ptr<sf::RectangleShape>> inter;
	inter.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(LEVEL_WIDTH, LEVEL_HEIGHT))));
	inter.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(GAME_WIDTH - LEVEL_WIDTH, 200.f))));
	inter.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(GAME_WIDTH - LEVEL_WIDTH, 300.f))));
	inter.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(GAME_WIDTH - LEVEL_WIDTH, 400.f))));
	inter.at(1)->setFillColor(Color::Blue);
	inter.at(1)->setPosition(Vector2f(LEVEL_WIDTH, 0));
	inter.at(2)->setFillColor(Color::Green);
	inter.at(2)->setPosition(Vector2f(LEVEL_WIDTH, 200.f));
	inter.at(3)->setFillColor(Color::Cyan);
	inter.at(3)->setPosition(Vector2f(LEVEL_WIDTH, 500.f));
	return inter;
}();
std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> HUD::panel1;
std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> HUD::panel2;
std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> HUD::panel3;

HUD::HUD() {
	addChild({ interface.at(0), interface.at(1), interface.at(2), interface.at(3) });
	getChildNode(interface[1].get())->addEventListener(sf::Event::EventType::MouseMoved,
		[this](game::Event * event) {
		interface.at(1)->setFillColor(Color(
			static_cast<Uint8>(event->mouseMove.x % 256),
			static_cast<Uint8>(event->mouseMove.x % 256),
			static_cast<Uint8>(event->mouseMove.y % 256),
			static_cast<Uint8>(255)
		));
	});
}

void HUD::setBackgroundColor(const sf::Color &color) {
	interface.at(0)->setFillColor(color);
}

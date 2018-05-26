#include "hud.h"
#include "define.h"
#include "area.h"

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
	std::shared_ptr<sf::CircleShape> up(new sf::CircleShape(50));
	up->setFillColor(sf::Color::Black);
	std::shared_ptr<sf::RectangleShape> over(new sf::RectangleShape(sf::Vector2f(100.f, 180.f)));
	over->setFillColor(sf::Color::Yellow);
	std::shared_ptr<sf::RectangleShape> down(new sf::RectangleShape(sf::Vector2f(80.f, 50.f)));
	down->setFillColor(sf::Color::Magenta);
	std::shared_ptr<sf::CircleShape> press(new sf::CircleShape(50));
	std::shared_ptr<game::CircleShapeNode> pressNode(new game::CircleShapeNode(press));
	button.reset(new game::Button(up, over, down, pressNode));
	button->setPosition(LEVEL_WIDTH + 20, 400);
	button->addEventListener(sf::Event::MouseButtonPressed,
		[](game::Event * event) {
		std::cout << "Mouse Pressed: " << std::get<sf::Event::MouseButtonEvent>(event->data).button
			<< ", x: " << std::get<sf::Event::MouseButtonEvent>(event->data).x
			<< ", y: " << std::get<sf::Event::MouseButtonEvent>(event->data).y
			<< std::endl;
	});
	addChild({ button });
}

void HUD::setBackgroundColor(const sf::Color &color) {
	interface.at(0)->setFillColor(color);
}

bool HUD::containsPoint(const sf::Vector2f & point) const {
	return Container::containsPoint(point);
}

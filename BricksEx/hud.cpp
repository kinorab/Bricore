#include "hud.h"
#include "define.h"
#include <iostream>

std::vector <std::shared_ptr<sf::RectangleShape>> HUD::interface = []() {
	std::vector <std::shared_ptr<sf::RectangleShape>> inter;
	inter.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(LEVEL_WIDTH, LEVEL_HEIGHT))));
	inter.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(GAME_WIDTH - LEVEL_WIDTH, 200.f))));
	inter.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(GAME_WIDTH - LEVEL_WIDTH, 300.f))));
	inter.push_back(std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(GAME_WIDTH - LEVEL_WIDTH, 400.f))));
	inter.at(1)->setFillColor(sf::Color::Blue);
	inter.at(1)->setPosition({ LEVEL_WIDTH, 0.f });
	inter.at(2)->setFillColor(sf::Color::Green);
	inter.at(2)->setPosition({ LEVEL_WIDTH, 200.f });
	inter.at(3)->setFillColor(sf::Color::Cyan);
	inter.at(3)->setPosition({ LEVEL_WIDTH, 500.f });
	return inter;
}();
std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> HUD::panel1;
std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> HUD::panel2;
std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> HUD::panel3;
std::shared_ptr<game::Button> HUD::button;
std::mutex HUD::mutex;
std::shared_ptr<HUD> HUD::instance = nullptr;

HUD::HUD() {
	std::shared_ptr<sf::CircleShape> up(new sf::CircleShape(50));
	up->setFillColor(sf::Color::Black);
	std::shared_ptr<sf::RectangleShape> over(new sf::RectangleShape(sf::Vector2f(100.f, 180.f)));
	over->setFillColor(sf::Color::Yellow);
	std::shared_ptr<sf::RectangleShape> down(new sf::RectangleShape(sf::Vector2f(80.f, 50.f)));
	down->setFillColor(sf::Color::Magenta);
	std::shared_ptr<sf::CircleShape> hit(new sf::CircleShape(50));
	std::shared_ptr<game::CircleShapeNode> hitNode(new game::CircleShapeNode(hit));
	button.reset(new game::Button(up, over, down, hitNode));
	button->setPosition(LEVEL_WIDTH + 20, 400);
	button->addEventListener(sf::Event::MouseButtonPressed,
		[](game::Event * event) {
		std::cout << "Mouse Pressed: " << std::get<sf::Event::MouseButtonEvent>(event->data).button
			<< ", x: " << std::get<sf::Event::MouseButtonEvent>(event->data).x
			<< ", y: " << std::get<sf::Event::MouseButtonEvent>(event->data).y
			<< std::endl;
	});
	addChild({ interface.at(0), interface.at(1), interface.at(2), interface.at(3), button });
}

std::shared_ptr<HUD> HUD::getInstance() {
	std::shared_ptr<HUD> HUDPtr = std::atomic_load_explicit(&instance, std::memory_order_acquire);
	if (!HUDPtr) {
		// prevent multithread get instance
		std::lock_guard<std::mutex> lock(mutex);
		HUDPtr = std::atomic_load_explicit(&instance, std::memory_order_relaxed);
		if (!HUDPtr) {
			HUDPtr = std::shared_ptr<HUD>(new HUD());
			std::atomic_store_explicit(&instance, HUDPtr, std::memory_order_release);
		}
	}
	return HUDPtr;
}

void HUD::setBackgroundColor(const sf::Color &color) {
	interface.at(0)->setFillColor(color);
}

bool HUD::containsPoint(const sf::Vector2f & point) const {
	return Container::containsPoint(point);
}

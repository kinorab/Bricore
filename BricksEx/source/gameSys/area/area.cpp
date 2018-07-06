#include "area.h"
#include "../../definition/gameState.h"
#include <SFML/Graphics.hpp>

using namespace game;

void Area::settleArea(const Label name, const sf::Vector2f & position) {
	switch (name) {
	case Label::Obstacle:
		obstacleArea->setPosition(position);
		break;
	case Label::Player:
		playerArea->setPosition(position);
		break;
	case Label::Wall:
		wallArea->setPosition(position);
		break;
	default:
		throw std::exception("Unexcept error.");
		break;
	}
}

void Area::settleArea(const Label name, const float height) {
	switch (name) {
	case Label::Obstacle:
		obstacleArea->setSize(sf::Vector2f(playerArea->getSize().x, height));
		break;
	case Label::Player:
		playerArea->setSize(sf::Vector2f(playerArea->getSize().x, height));
		break;
	case Label::Wall:
		wallArea->setSize(sf::Vector2f(playerArea->getSize().x, height));
		break;
	default:
		throw std::exception("Unexcept error.");
		break;
	}
}

void Area::settleArea(const Label name, const sf::Vector2f & position, const float height) {
	settleArea(name, position);
	settleArea(name, height);
}

void Area::setAreaOutline(const Label name, const sf::Color & color) {
	switch (name) {
	case Label::Obstacle:
		obstacleArea->setOutlineColor(color);
		break;
	case Label::Player:
		playerArea->setOutlineColor(color);
		break;
	case Label::Wall:
		wallArea->setOutlineColor(color);
		break;
	default:
		throw std::exception("Unexcept error.");
		break;
	}
}

void Area::setAreaOutline(const Label name, const float thickness) {
	switch (name) {
	case Label::Obstacle:
		obstacleArea->setOutlineThickness(thickness);
		break;
	case Label::Player:
		playerArea->setOutlineThickness(thickness);
		break;
	case Label::Wall:
		wallArea->setOutlineThickness(thickness);
		break;
	default:
		throw std::exception("Unexcept error.");
		break;
	}
}

void Area::setAreaOutline(const Label name, const float thickness, const sf::Color & color) {
	setAreaOutline(name, thickness);
	setAreaOutline(name, color);
}

const sf::RectangleShape & Area::getArea(const Label name) const {
	switch (name) {
	case Label::Obstacle:
		return *obstacleArea;
		break;
	case Label::Player:
		return *playerArea;
		break;
	case Label::Wall:
		return *wallArea;
		break;
	default:
		throw std::exception("Unexcept error.");
		break;
	}
}

Area::Area()
	: playerArea(new sf::RectangleShape(sf::Vector2f(LEVEL_WIDTH, 0.f)))
	, wallArea(new sf::RectangleShape(sf::Vector2f(LEVEL_WIDTH, 0.f)))
	, obstacleArea(new sf::RectangleShape(sf::Vector2f(LEVEL_WIDTH, 0.f))) {
	playerArea->setOutlineThickness(7.f);
	wallArea->setOutlineThickness(7.f);
	obstacleArea->setOutlineThickness(7.f);
}

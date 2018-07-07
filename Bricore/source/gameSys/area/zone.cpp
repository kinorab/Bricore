#include "zone.h"
#include "../../definition/gameState.h"
#include <SFML/Graphics.hpp>
#include "zone.h"

using namespace game;

void Zone::settleZone(const Label name, const sf::Vector2f & position) {
	switch (name) {
	case Label::Obstacle:
		obstacleZone->setPosition(position);
		break;
	case Label::Player:
		playerZone->setPosition(position);
		break;
	case Label::Wall:
		wallZone->setPosition(position);
		break;
	default:
		throw std::exception("Unexcept error.");
		break;
	}
}

void Zone::settleZone(const Label name, const float height) {
	switch (name) {
	case Label::Obstacle:
		obstacleZone->setSize(sf::Vector2f(obstacleZone->getSize().x, height));
		break;
	case Label::Player:
		playerZone->setSize(sf::Vector2f(playerZone->getSize().x, height));
		break;
	case Label::Wall:
		wallZone->setSize(sf::Vector2f(wallZone->getSize().x, height));
		break;
	default:
		throw std::exception("Unexcept error.");
		break;
	}
}

void Zone::settleZone(const Label name, const sf::Vector2f & position, const float height) {
	settleZone(name, position);
	settleZone(name, height);
}

void Zone::setZoneOutline(const Label name, const sf::Color & color) {
	switch (name) {
	case Label::Obstacle:
		obstacleZone->setOutlineColor(color);
		break;
	case Label::Player:
		playerZone->setOutlineColor(color);
		break;
	case Label::Wall:
		wallZone->setOutlineColor(color);
		break;
	default:
		throw std::exception("Unexcept error.");
		break;
	}
}

void Zone::setZoneOutline(const Label name, const float thickness) {
	switch (name) {
	case Label::Obstacle:
		obstacleZone->setOutlineThickness(thickness);
		break;
	case Label::Player:
		playerZone->setOutlineThickness(thickness);
		break;
	case Label::Wall:
		wallZone->setOutlineThickness(thickness);
		break;
	default:
		throw std::exception("Unexcept error.");
		break;
	}
}

void Zone::setZoneOutline(const Label name, const float thickness, const sf::Color & color) {
	setZoneOutline(name, thickness);
	setZoneOutline(name, color);
}

const sf::RectangleShape & Zone::getZone(const Label name) const {
	switch (name) {
	case Label::Obstacle:
		return *obstacleZone;
		break;
	case Label::Player:
		return *playerZone;
		break;
	case Label::Wall:
		return *wallZone;
		break;
	default:
		throw std::exception("Unexcept error.");
		break;
	}
}

Zone::Zone()
	: playerZone(new sf::RectangleShape(sf::Vector2f(LEVEL_WIDTH, 0.f)))
	, wallZone(new sf::RectangleShape(sf::Vector2f(LEVEL_WIDTH, 0.f)))
	, obstacleZone(new sf::RectangleShape(sf::Vector2f(LEVEL_WIDTH, 0.f))) {
	playerZone->setOutlineThickness(7.f);
	wallZone->setOutlineThickness(7.f);
	obstacleZone->setOutlineThickness(7.f);
}

Zone::~Zone() {
}

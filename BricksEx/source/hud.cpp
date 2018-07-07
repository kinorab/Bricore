#include "hud.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include <SFML/Graphics.hpp>

float panelWidth = GAME_WIDTH - LEVEL_WIDTH;

HUD::HUD()
	: bossPanel{ false, std::make_shared<sf::RectangleShape>(sf::Vector2f(panelWidth, 200.f)), {} }
	, scorePanel{ true, std::make_shared<sf::RectangleShape>(sf::Vector2f(panelWidth, 300.f)), {} }
	, playerPanel{ true, std::make_shared<sf::RectangleShape>(sf::Vector2f(panelWidth, 400.f)), {} } {
	// interfaces
	interfaces.emplace(BattleArea, std::make_shared<sf::RectangleShape>(sf::Vector2f(LEVEL_WIDTH, LEVEL_HEIGHT)));
	interfaces.at(BattleArea)->setFillColor(sf::Color(180, 180, 180));
	// panels
	bossPanel.background->setFillColor(sf::Color::Blue);
	bossPanel.background->setPosition({ LEVEL_WIDTH, 0.f });
	scorePanel.background->setFillColor(sf::Color::Green);
	scorePanel.background->setPosition({ LEVEL_WIDTH, 200.f });
	playerPanel.background->setFillColor(sf::Color::Cyan);
	playerPanel.background->setPosition({ LEVEL_WIDTH, 500.f });
	addChild({ interfaces.at(BattleArea), bossPanel.background, scorePanel.background, playerPanel.background });
	// button
	// addChild({ button });
}

bool HUD::containsPoint(const sf::Vector2f & point) const {
	return Container::containsPoint(point);
}

HUD::~HUD() {
}

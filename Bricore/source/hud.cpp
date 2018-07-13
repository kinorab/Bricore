#include "hud.h"
#include "UI/button.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "event/eventListener.h"
#include "handler/keyboardHandler.h"
#include "handler/mouseHandler.h"
#include "event/keyboard/keyEvent.h"
#include "event/mouse/mouseEvent.h"
#include <SFML/Graphics.hpp>

using namespace game;

float panelWidth = GAME_WIDTH - LEVEL_WIDTH;

HUD::HUD(const InterfaceCategory interface)
	: bossPanel{ false, std::make_shared<sf::RectangleShape>(sf::Vector2f(panelWidth, 200.f)), {} }
	, scorePanel{ false, std::make_shared<sf::RectangleShape>(sf::Vector2f(panelWidth, 300.f)), {} }
	, playerPanel{ false, std::make_shared<sf::RectangleShape>(sf::Vector2f(panelWidth, 400.f)), {} }
	, currentInterface(interface) {
	// initialize interfaces
	interfaces.emplace(Main, std::make_shared<sf::RectangleShape>(sf::Vector2f(GAME_WIDTH, GAME_HEIGHT)));
	interfaces.at(Main)->setFillColor(sf::Color::White);
	interfaces.emplace(BattleArea, std::make_shared<sf::RectangleShape>(sf::Vector2f(LEVEL_WIDTH, LEVEL_HEIGHT)));
	// make residue Shadow
	interfaces.at(BattleArea)->setFillColor(sf::Color(180, 180, 180, 200));
	// initialize panels
	bossPanel.context->setFillColor(sf::Color::Blue);
	bossPanel.context->setPosition({ LEVEL_WIDTH, 0.f });
	scorePanel.context->setFillColor(sf::Color::Green);
	scorePanel.context->setPosition({ LEVEL_WIDTH, 200.f });
	playerPanel.context->setFillColor(sf::Color::Cyan);
	playerPanel.context->setPosition({ LEVEL_WIDTH, 500.f });
	addChild({ interfaces.at(BattleArea), bossPanel.context, scorePanel.context, playerPanel.context, interfaces.at(Main) });
	// initialize button
}

bool HUD::containsPoint(const sf::Vector2f & point) const {
	return Container::containsPoint(point);
}

std::shared_ptr<sf::Drawable> HUD::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void HUD::changeInterface(const InterfaceCategory nextInterface) {
	// add next interface event listener
	// addListener()
	// remove current interface event listener
	// removeListener()
	// set interface
	currentInterface = nextInterface;
}

HUD::~HUD() {
}

void HUD::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	switch (currentInterface) {
	case InterfaceCategory::Main:
		target.draw(*interfaces.at(Main), states);
		break;
	case InterfaceCategory::SaveLoad:
		break;
	case InterfaceCategory::Setting:
		break;
	case InterfaceCategory::PrepareArea:
		break;
	case InterfaceCategory::Store:
		break;
	case InterfaceCategory::IllustratedList:
		break;
	case InterfaceCategory::BattleArea:
		target.draw(*interfaces.at(BattleArea), states);
		target.draw(*bossPanel.context, states);
		target.draw(*scorePanel.context, states);
		target.draw(*playerPanel.context, states);
		break;
	default:
		throw std::exception("Unexcept error.");
	}
}

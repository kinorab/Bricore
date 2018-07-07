#pragma once

#include "UI/button.h"

namespace sf {
	class Color;
	class RectangleShape;
}

class HUD :
	public game::Container {
public:
	enum InterfaceCategory {
		MainPage,
		BattleArea,
		Store
	};
	HUD();
	virtual bool containsPoint(const sf::Vector2f & point) const override;
	virtual ~HUD();

protected:
	struct Compnonent {
		size_t uData;
		bool bShow;
		std::shared_ptr<sf::RectangleShape> context;
	};

private:
	struct Panel {
		bool bDisplay;
		std::shared_ptr<sf::RectangleShape> background;
		std::map<std::string, Compnonent> compnonents;
	};
	std::map<InterfaceCategory, std::shared_ptr<sf::RectangleShape>> interfaces;
	Panel bossPanel;
	Panel scorePanel;
	Panel playerPanel;
	// std::shared_ptr<Button> button;
};
#pragma once

#include "button.h"
#include <SFML/Graphics.hpp>

namespace game {
	class Area;
}

class HUD :
	public game::Container {
public:
	HUD();
	virtual void setBackgroundColor(const sf::Color &);
	virtual bool containsPoint(const sf::Vector2f & point) const override;

private:
	std::unique_ptr<game::Area> area;
	std::vector <std::shared_ptr<sf::RectangleShape>> interface;
	std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> panel1;
	std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> panel2;
	std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> panel3;
	std::shared_ptr<game::Button> button;

};
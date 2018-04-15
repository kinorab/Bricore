#pragma once

#include "button.h"
#include <SFML/Graphics.hpp>

class HUD :
	public game::Container {
public:
	HUD();
	static void setBackgroundColor(const sf::Color &);
	virtual bool containsPoint(const sf::Vector2f & point) const override;
private:
	static std::vector <std::shared_ptr<sf::RectangleShape>> interface;
	static std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> panel1;
	static std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> panel2;
	static std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> panel3;
	static std::shared_ptr<game::Button> button;
};
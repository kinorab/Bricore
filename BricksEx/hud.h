#pragma once

#include "container.h"
#include <SFML/Graphics.hpp>
#include <utility>

class HUD :
	public game::Container {
public:
	HUD();
	static void setBackgroundColor(const sf::Color &);
private:
	static std::vector <std::shared_ptr<sf::RectangleShape>> interface;
	static std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> panel1;
	static std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> panel2;
	static std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> panel3;
};
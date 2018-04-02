#pragma once

#include "container.h"
#include <SFML/Graphics.hpp>
#include <utility>

class HUD :
	public game::Container {
public:
	HUD();
private:
	std::vector <std::shared_ptr<sf::RectangleShape>> background;
	std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> panel1;
	std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> panel2;
	std::map <std::string, std::pair<std::shared_ptr<sf::RectangleShape>, size_t>> panel3;
};
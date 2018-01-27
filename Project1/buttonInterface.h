#pragma once

#include <SFML/Graphics.hpp>

class ButtonInterface {
public:
	virtual void checkClick(sf::Vector2f mousePos) = 0;
	virtual void setCaption(std::string caption) = 0;
	virtual std::string getCaption() = 0;
	virtual ~ButtonInterface() = 0;
};

ButtonInterface::~ButtonInterface() {

}
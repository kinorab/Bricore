#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class ButtonInterface {
public:
	static std::unique_ptr<ButtonInterface> create(const sf::Texture & up, const sf::Texture & over, const sf::Texture & down, sf::FloatRect hitArea, std::string caption, sf::Vector2f location);
	virtual void checkClick(sf::Vector2f mousePos) = 0;
	virtual void setCaption(std::string caption) = 0;
	virtual std::string getCaption() = 0;
	virtual ~ButtonInterface() { };
};
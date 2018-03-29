#include "UIFactory.h"

std::unique_ptr<Button> UIFactory::createButton(const sf::Texture & up, const sf::Texture & over, const sf::Texture & down, sf::FloatRect hitArea, std::string caption) {
	return std::unique_ptr<Button>(new Button());
}
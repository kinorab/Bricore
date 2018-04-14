#include "UIFactory.h"

std::unique_ptr<game::Button> UIFactory::createButton(const sf::Texture & up, const sf::Texture & over, const sf::Texture & down, sf::FloatRect hitArea, std::string caption) {
	return std::unique_ptr<game::Button>(new game::Button());
}
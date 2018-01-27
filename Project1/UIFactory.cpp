#include "UIFactory.h"
#include "button.h"

using namespace std;
using namespace sf;

static std::unique_ptr<ButtonInterface> createButton(const sf::Texture & up, const sf::Texture & over, const sf::Texture & down, sf::FloatRect hitArea, std::string caption, sf::Vector2f location) {
	return unique_ptr<ButtonInterface>(new Button(up, over, down, hitArea, caption, location));
}
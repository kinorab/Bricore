#include "textField.h"

namespace game {
	game::TextField::TextField(std::string text) {
	}

	TextField::~TextField() {
	}

	bool TextField::containsPoint(const sf::Vector2f & point) const	{
		return false;
	}

	std::shared_ptr<sf::Drawable> TextField::getDrawable() const {
		return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
	}

	int TextField::getLength() const {
		return content.size();
	}

	void TextField::draw(sf::RenderTarget & target, sf::RenderStates states) const {

	}

}
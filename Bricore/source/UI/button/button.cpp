#include "button.h"
#include <SFML/Graphics.hpp>

namespace game {
	bool Button::isReleasing() const {
		return bReleasing;
	}

	Button::State Button::getState() const {
		return currentState;
	}

	Button::~Button() {
	}

	std::shared_ptr<sf::Drawable> Button::getDrawable() const {
		return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
	}

	Button::Button()
		: bReleasing(false)
		, currentState(State::Up) {
	}
}
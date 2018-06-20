#include "button.h"
#include "../definition/utility.h"
#include "../event/mouse/mouseEvent.h"
#include "../event/mouse/mouseListener.h"
#include <SFML/Graphics.hpp>

namespace game {
	Button::Button(std::shared_ptr<sf::Sprite> upObject, std::shared_ptr<sf::Drawable> overObject, std::shared_ptr<sf::Drawable> downObject)
		: upObject(upObject)
		, overObject(overObject)
		, downObject(downObject)
		, hitObject(new SpriteNode(upObject)) {
		using namespace std::placeholders;
		addListener(std::make_shared<MouseEnteredListener>(std::bind(&Button::onMouseEntered, this, _1)));
		addListener(std::make_shared<MouseLeftListener>(std::bind(&Button::onMouseLeft, this, _1)));
		addListener(std::make_shared<MousePressedListener>(std::bind(&Button::onMousePressed, this, _1)));
		addListener(std::make_shared<MouseReleasedListener>(std::bind(&Button::onMouseReleased, this, _1)));
	}

	Button::~Button() {

	}

	bool Button::containsPoint(const sf::Vector2f & point) const {
		return hitObject->containsPoint(getTransform().getInverse().transformPoint(point));
	}

	std::shared_ptr<sf::Drawable> Button::getDrawable() const {
		switch (currentState) {
		case ButtonState::UP:
			return upObject;
			break;
		case ButtonState::OVER:
			return overObject;
			break;
		case ButtonState::DOWN:
			return downObject;
			break;
		default:
			return nullptr;
			break;
		}
	}

	void Button::onMouseEntered(MouseEnteredEvent &) {
		currentState = ButtonState::OVER;
	}

	void Button::onMouseLeft(MouseLeftEvent &) {
		currentState = ButtonState::UP;
	}

	void Button::onMousePressed(MousePressedEvent &) {
		currentState = ButtonState::DOWN;
	}

	void Button::onMouseReleased(MouseReleasedEvent &) {
		currentState = ButtonState::OVER;
	}
}
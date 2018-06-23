#include "button.h"
#include "../definition/utility.h"
#include "../event/mouse/mouseEvent.h"
#include "../event/eventListener.h"
#include <SFML/Graphics.hpp>

namespace game {
	Button::Button(std::shared_ptr<sf::Sprite> upObject, std::shared_ptr<sf::Drawable> overObject, std::shared_ptr<sf::Drawable> downObject)
		: upObject(upObject)
		, overObject(overObject)
		, downObject(downObject)
		, hitObject(new SpriteNode(upObject)) {
		addListener(std::make_shared<EventListener<MouseEnteredEvent>>([&](auto & event) {onMouseEntered(event); }));
		addListener(std::make_shared<EventListener<MouseLeftEvent>>([&](auto & event) {onMouseLeft(event); }));
		addListener(std::make_shared<EventListener<MousePressedEvent>>([&](auto & event) {onMousePressed(event); }));
		addListener(std::make_shared<EventListener<MouseReleasedEvent>>([&](auto & event) {onMouseReleased(event); }));
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
#include "button.h"
#include "../definition/utility.h"
#include "../event/mouseButtonListener.h"
#include "../event/mouseMoveListener.h"
#include <SFML/Graphics.hpp>

namespace game {
	Button::Button(std::shared_ptr<sf::Sprite> upObject, std::shared_ptr<sf::Drawable> overObject, std::shared_ptr<sf::Drawable> downObject)
		: upObject(upObject)
		, overObject(overObject)
		, downObject(downObject)
		, hitObject(new SpriteNode(upObject)) {
		using namespace std::placeholders;
		addListener(EventType::MouseEntered, std::make_shared<MouseMoveListener>(std::bind(&Button::onMouseEntered, this, _1)));
		addListener(EventType::MouseMoved, std::make_shared<MouseMoveListener>(std::bind(&Button::onMouseLeft, this, _1)));
		addListener(EventType::MouseButtonPressed, std::make_shared<MouseButtonListener>(std::bind(&Button::onMousePressed, this, _1)));
		addListener(EventType::MouseButtonReleased, std::make_shared<MouseButtonListener>(std::bind(&Button::onMouseReleased, this, _1)));
	}

	Button::~Button() {

	}

	bool Button::containsPoint(const sf::Vector2f & point) const {
		return hitObject->containsPoint(getTransform().getInverse().transformPoint(point));
	}

	std::shared_ptr<sf::Drawable> Button::getDrawable() const {
		switch (currentState) {
		case game::Button::ButtonState::UP:
			return upObject;
			break;
		case game::Button::ButtonState::OVER:
			return overObject;
			break;
		case game::Button::ButtonState::DOWN:
			return downObject;
			break;
		default:
			return nullptr;
			break;
		}
	}

	void Button::onMouseEntered(MouseMoveEvent &) {
		currentState = ButtonState::OVER;
	}

	void Button::onMouseLeft(MouseMoveEvent &) {
		currentState = ButtonState::UP;
	}

	void Button::onMousePressed(MouseButtonEvent &) {
		currentState = ButtonState::DOWN;
	}

	void Button::onMouseReleased(MouseButtonEvent &) {
		currentState = ButtonState::OVER;
	}
}
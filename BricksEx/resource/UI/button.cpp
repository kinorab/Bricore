#include "button.h"
#include "../definition/utility.h"
#include "../definition/intersects.h"

namespace game {
	Button::Button(std::shared_ptr<sf::Drawable> upObject, std::shared_ptr<sf::Drawable> overObject, std::shared_ptr<sf::Drawable> downObject, std::shared_ptr<game::InteractiveObject> hitObject) {
		this->upObject = upObject;
		this->overObject = overObject;
		this->downObject = downObject;
		this->hitObject = hitObject;
		using namespace std::placeholders;
		addEventListener(sf::Event::MouseEntered, std::bind(&Button::onMouseEntered, this, _1));
		addEventListener(sf::Event::MouseLeft, std::bind(&Button::onMouseLeft, this, _1));
		addEventListener(sf::Event::MouseButtonPressed, std::bind(&Button::onMousePressed, this, _1));
		addEventListener(sf::Event::MouseButtonReleased, std::bind(&Button::onMouseReleased, this, _1));
	}

	Button::Button(std::shared_ptr<sf::Sprite> upObject, std::shared_ptr<sf::Drawable> overObject, std::shared_ptr<sf::Drawable> downObject) {
		this->upObject = upObject;
		this->overObject = overObject;
		this->downObject = downObject;
		this->hitObject.reset(new SpriteNode(upObject));
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

	void Button::onMouseEntered(Event *) {
		currentState = ButtonState::OVER;
	}

	void Button::onMouseLeft(Event *) {
		currentState = ButtonState::UP;
	}

	void Button::onMousePressed(Event *) {
		currentState = ButtonState::DOWN;
	}

	void Button::onMouseReleased(game::Event *) {
		currentState = ButtonState::OVER;
	}
}
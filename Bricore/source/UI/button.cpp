#include "button.h"
#include "../definition/utility.h"
#include "../manager/textureManager.h"
#include "../event/mouse/mouseEvent.h"
#include "../event/eventListener.h"
#include <SFML/Graphics.hpp>

namespace game {
	Button::Button(const std::shared_ptr<sf::Texture> & upTexture
		, const std::shared_ptr<sf::Texture> & overTexture
		, const std::shared_ptr<sf::Texture> & downTexture, const ButtonShape shape)
		: releaseObject(nullptr)
		, buttonShape(shape)
		, bReleasing(false) {
		initializeButton(false);
		settleButtonSize(upTexture, overTexture, downTexture);
	}

	Button::Button(const std::shared_ptr<sf::Texture>& upTexture
		, const std::shared_ptr<sf::Texture>& overTexture
		, const std::shared_ptr<sf::Texture>& downTexture
		, const std::shared_ptr<sf::Texture>& releaseTexture, const ButtonShape shape
		, const sf::Time & specialDuration)
		: buttonShape(shape)
		, bReleasing(false)
		, specialDuration(specialDuration) {
		initializeButton(true);
		settleButtonSize(upTexture, overTexture, downTexture, releaseTexture);
	}

	Button::~Button() {
	}

	bool Button::containsPoint(const sf::Vector2f & point) const {
		auto circleContains = [&](std::shared_ptr<sf::CircleShape> & object) {
			const sf::Vector2f displacement = point - object->getPosition();
			if (pow(displacement.x, 2) + pow(displacement.y, 2) <= pow(object->getRadius(), 2)) {
				return true;
			}
			return false;
		};
		switch (currentState) {
		case ButtonState::Up:
			if (auto up = std::dynamic_pointer_cast<sf::CircleShape>(upObject)) {
				return circleContains(up);
			}
			return upObject->getGlobalBounds().contains(point);
			break;
		case ButtonState::Over:
			if (auto over = std::dynamic_pointer_cast<sf::CircleShape>(overObject)) { 
				return circleContains(over); 
			}
			return overObject->getGlobalBounds().contains(point);
			break;
		case ButtonState::Down:
			if (auto down = std::dynamic_pointer_cast<sf::CircleShape>(downObject)) {
				return circleContains(down);
			}
			return downObject->getGlobalBounds().contains(point);
			break;
			// use over state contain point
		case ButtonState::Release:
			if (auto over = std::dynamic_pointer_cast<sf::CircleShape>(overObject)) {
				return circleContains(over);
			}
			return overObject->getGlobalBounds().contains(point);
			break;
		default:
			throw std::exception("Unexcept error");
		}
	}

	std::shared_ptr<sf::Drawable> Button::getDrawable() const {
		return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
	}

	void Button::setSpecialEffectObacity(const sf::Uint8 a) {
		if (!releaseObject) return;
		releaseObject->setFillColor(sf::Color(sf::Color::Transparent.r, sf::Color::Transparent.b
			, sf::Color::Transparent.g, a));
	}

	void Button::onMouseEntered() {
		if (bReleasing) return;
		currentState = ButtonState::Over;
	}

	void Button::onMouseLeft() {
		if (bReleasing) return;
		currentState = ButtonState::Up;
	}

	void Button::onMousePressed(MousePressedEvent &) {
		currentState = ButtonState::Down;
		// press again will cancel current releasing special effect
		bReleasing = false;
	}

	void Button::onMouseReleased(MouseReleasedEvent &) {
		if (releaseObject) {
			if (!bReleasing) {
				bReleasing = true;
				currentState = ButtonState::Release;
				clock.restart();
			}
			else if (clock.getElapsedTime() > specialDuration) {
				bReleasing = false;
				currentState = ButtonState::Over;
			}
		}
		else {
			currentState = ButtonState::Over;
		}
	}

	void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		switch (currentState) {
		case ButtonState::Up:
			target.draw(*upObject, states);
			break;
		case ButtonState::Over:
			target.draw(*overObject, states);
			break;
		case ButtonState::Down:
			target.draw(*downObject, states);
			break;
		case ButtonState::Release:
			target.draw(*overObject, states);
			target.draw(*releaseObject, states);
			break;
		default:
			throw std::exception("Unexcept error");
		}
	}

	void Button::initializeButton(const bool isReleaseSpecialize) {
		switch (buttonShape) {
		case ButtonShape::Circle:
			upObject.reset(new sf::CircleShape);
			overObject.reset(new sf::CircleShape);
			downObject.reset(new sf::CircleShape);
			if (isReleaseSpecialize) {
				releaseObject.reset(new sf::CircleShape);
			}
			break;
		case ButtonShape::Rectangle:
			upObject.reset(new sf::RectangleShape);
			overObject.reset(new sf::RectangleShape);
			downObject.reset(new sf::RectangleShape);
			if (isReleaseSpecialize) {
				releaseObject.reset(new sf::RectangleShape);
			}
			break;
		default:
			throw std::exception("Unexcept error.");
		}
		addListener(std::make_shared<EventListener<MouseEnteredEvent>>([&] { onMouseEntered(); }));
		addListener(std::make_shared<EventListener<MouseLeftEvent>>([&] { onMouseLeft(); }));
		addListener(std::make_shared<EventListener<MousePressedEvent>>([&](auto & event) { onMousePressed(event); }));
		addListener(std::make_shared<EventListener<MouseReleasedEvent>>([&](auto & event) { onMouseReleased(event); }));
	}

	void Button::settleButtonSize(const std::shared_ptr<sf::Texture>& upTexture
		, const std::shared_ptr<sf::Texture>& overTexture
		, const std::shared_ptr<sf::Texture>& downTexture
		, const std::shared_ptr<sf::Texture>& releaseTexture) {
		if (auto release = std::dynamic_pointer_cast<sf::CircleShape>(releaseObject)) {
			release->setRadius(releaseTexture->getSize().x / 2.f);
			release->setTexture(releaseTexture.get(), true);
		}
		else if (auto release = std::dynamic_pointer_cast<sf::RectangleShape>(releaseObject)) {
			release->setSize(static_cast<sf::Vector2f>(releaseTexture->getSize()));
			release->setTexture(releaseTexture.get(), true);
		}
		settleButtonSize(upTexture, overTexture, releaseTexture);
	}

	void Button::settleButtonSize(const std::shared_ptr<sf::Texture>& upTexture
		, const std::shared_ptr<sf::Texture>& overTexture, const std::shared_ptr<sf::Texture>& downTexture) {
		switch (buttonShape) {
		case ButtonShape::Circle:
		{
			auto up = std::dynamic_pointer_cast<sf::CircleShape>(upObject);
			auto over = std::dynamic_pointer_cast<sf::CircleShape>(overObject);
			auto down = std::dynamic_pointer_cast<sf::CircleShape>(downObject);
			up->setRadius(upTexture->getSize().x / 2.f);
			up->setTexture(upTexture.get(), true);
			over->setRadius(overTexture->getSize().x / 2.f);
			over->setTexture(overTexture.get(), true);
			down->setRadius(downTexture->getSize().x / 2.f);
			down->setTexture(downTexture.get(), true);
		}
		break;
		case ButtonShape::Rectangle:
		{
			auto up = std::dynamic_pointer_cast<sf::RectangleShape>(upObject);
			auto over = std::dynamic_pointer_cast<sf::RectangleShape>(overObject);
			auto down = std::dynamic_pointer_cast<sf::RectangleShape>(downObject);
			up->setSize(static_cast<sf::Vector2f>(upTexture->getSize()));
			up->setTexture(upTexture.get(), true);
			over->setSize(static_cast<sf::Vector2f>(overTexture->getSize()));
			over->setTexture(overTexture.get(), true);
			down->setSize(static_cast<sf::Vector2f>(downTexture->getSize()));
			down->setTexture(downTexture.get(), true);
		}
		break;
		default:
			throw std::exception("Unexcept error.");
		}
	}
}
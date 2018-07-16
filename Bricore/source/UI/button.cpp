#include "button.h"
#include "../definition/utility.h"
#include "../manager/textureManager.h"
#include "../event/mouse/mouseEvent.h"
#include "../event/eventListener.h"
#include <SFML/Graphics.hpp>

namespace game {
	Button::Button(const std::string & upTextureFile
		, const std::string & overTextureFile
		, const std::string & downTextureFile
		, const ButtonShape shape)
		: currentState(Up)
		, buttonShape(shape)
		, bReleasing(false) {
		textures.emplace(Up, TextureManager::getInstance().get(upTextureFile));
		textures.emplace(Over, TextureManager::getInstance().get(overTextureFile));
		textures.emplace(Down, TextureManager::getInstance().get(downTextureFile));
		initializeButton(false);
	}

	Button::Button(const std::string & upTextureFile
		, const std::string & overTextureFile
		, const std::string & downTextureFile
		, const std::string & releaseTextureFile
		, const ButtonShape shape, const sf::Time & specialDuration)
		: currentState(Up)
		, buttonShape(shape)
		, bReleasing(false)
		, specialDuration(specialDuration) {
		textures.emplace(Up, TextureManager::getInstance().get(upTextureFile));
		textures.emplace(Over, TextureManager::getInstance().get(overTextureFile));
		textures.emplace(Down, TextureManager::getInstance().get(downTextureFile));
		textures.emplace(Release, TextureManager::getInstance().get(releaseTextureFile));
		initializeButton(true);
	}

	Button::~Button() {
	}

	bool Button::containsPoint(const sf::Vector2f & point) const {
		auto circleContains = [&](const std::shared_ptr<const sf::CircleShape> & object) {
			const sf::Vector2f displacement = point - object->getPosition();
			if (pow(displacement.x, 2) + pow(displacement.y, 2) <= pow(object->getRadius(), 2)) {
				return true;
			}
			return false;
		};
		// release state use over state contain point
		ButtonState state = currentState == Release ? Over : currentState;
		if (auto circle = std::dynamic_pointer_cast<const sf::CircleShape>(objects.at(state))) {
			return circleContains(circle);
		}
		return objects.at(state)->getGlobalBounds().contains(point);
	}

	std::shared_ptr<sf::Drawable> Button::getDrawable() const {
		return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
	}

	void Button::setSpecialEffectObacity(const sf::Uint8 a) {
		if (objects.count(Release) == 0) return;
		objects[Release]->setFillColor(sf::Color(sf::Color::Transparent.r, sf::Color::Transparent.b
			, sf::Color::Transparent.g, a));
	}

	void Button::onMouseEntered() {
		if (bReleasing) return;
		currentState = Over;
	}

	void Button::onMouseLeft() {
		if (bReleasing) return;
		currentState = Up;
	}

	void Button::onMousePressed(MousePressedEvent & event) {
		currentState = Down;
		// press again will cancel current releasing special effect
		bReleasing = false;
	}

	void Button::onMouseReleased(MouseReleasedEvent & event) {
		if (objects.count(Release) != 0) {
			if (!bReleasing) {
				bReleasing = true;
				currentState = Release;
				clock.restart();
			}
			else if (clock.getElapsedTime() > specialDuration) {
				bReleasing = false;
				currentState = Over;
			}
		}
		else {
			currentState = Over;
		}
	}

	void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		if (currentState == Release) {
			target.draw(*objects.at(Over), states);
			target.draw(*objects.at(currentState), states);
		}
		else {
			target.draw(*objects.at(currentState), states);
		}
	}

	void Button::initializeButton(const bool isReleaseSpecialize) {
		switch (buttonShape) {
		case ButtonShape::Circle:
			objects.emplace(ButtonState::Up, new sf::CircleShape);
			objects.emplace(ButtonState::Over, new sf::CircleShape);
			objects.emplace(ButtonState::Down, new sf::CircleShape);
			if (isReleaseSpecialize) {
				objects.emplace(ButtonState::Release, new sf::CircleShape);
			}
			break;
		case ButtonShape::Rectangle:
			objects.emplace(ButtonState::Up, new sf::RectangleShape);
			objects.emplace(ButtonState::Over, new sf::RectangleShape);
			objects.emplace(ButtonState::Down, new sf::RectangleShape);
			if (isReleaseSpecialize) {
				objects.emplace(ButtonState::Release, new sf::RectangleShape);
			}
			break;
		default:
			throw std::exception("Unexcept error.");
		}
		settleButtonSize();
		addListener(std::make_shared<EventListener<MouseEnteredEvent>>([&] { onMouseEntered(); }));
		addListener(std::make_shared<EventListener<MouseLeftEvent>>([&] { onMouseLeft(); }));
		addListener(std::make_shared<EventListener<MousePressedEvent>>([&](auto & event) { onMousePressed(event); }));
		addListener(std::make_shared<EventListener<MouseReleasedEvent>>([&](auto & event) { onMouseReleased(event); }));
	}

	void Button::settleButtonSize() {
		std::for_each(textures.begin(), textures.end()
			, [this](const std::pair<ButtonState, std::shared_ptr<sf::Texture>> & texture) {
			objects[texture.first]->setTexture(texture.second.get(), true);
			if (auto object = std::dynamic_pointer_cast<sf::CircleShape>(objects[texture.first])) {
				object->setRadius(texture.second->getSize().x / 2.f);
			}
			else if (auto object = std::dynamic_pointer_cast<sf::RectangleShape>(objects[texture.first])) {
				object->setSize(sf::Vector2f(texture.second->getSize()));
			}
		});
	}
}
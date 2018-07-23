#include "circleButton.h"
#include "../../definition/utility.h"
#include "../../manager/textureManager.h"
#include "../../event/mouse/mouseEvent.h"
#include "../../event/eventListener.h"
#include <SFML/Graphics.hpp>

using namespace game;

std::map<CircleButton::Name, CircleButton::StateString> CircleButton::fileNames({

	});

CircleButton::CircleButton(const Name name)
	: specialDuration(sf::seconds(0))
	, currentEffect(SpecialEffect::None) {
	auto upTexture = TextureManager::getInstance().get(fileNames[name].buttonUp);
	auto overTexture = TextureManager::getInstance().get(fileNames[name].buttonOver);
	auto downTexture = TextureManager::getInstance().get(fileNames[name].buttonDown);
	circleButton = { 
		std::pair(State::Up, std::make_shared<sf::CircleShape>(upTexture->getSize().x * 0.5f))
		, std::pair(State::Over, std::make_shared<sf::CircleShape>(overTexture->getSize().x * 0.5f))
		, std::pair(State::Down, std::make_shared<sf::CircleShape>(downTexture->getSize().x * 0.5f))
		, std::pair(State::Release, nullptr)
	};
	circleButton[State::Up]->setTexture(upTexture);
	circleButton[State::Over]->setTexture(overTexture);
	circleButton[State::Down]->setTexture(downTexture);
	initialize();
}

CircleButton::CircleButton(const Name name, const SpecialEffect effect, const sf::Time & duration)
	: specialDuration(duration)
	, currentEffect(effect) {
	auto upTexture = TextureManager::getInstance().get(fileNames[name].buttonUp);
	auto overTexture = TextureManager::getInstance().get(fileNames[name].buttonOver);
	auto downTexture = TextureManager::getInstance().get(fileNames[name].buttonDown);
	auto releaseTexture = TextureManager::getInstance().get(fileNames[name].buttonRelease);
	circleButton = {
		std::pair(State::Up, std::make_shared<sf::CircleShape>(upTexture->getSize().x * 0.5f))
		, std::pair(State::Over, std::make_shared<sf::CircleShape>(overTexture->getSize().x * 0.5f))
		, std::pair(State::Down, std::make_shared<sf::CircleShape>(downTexture->getSize().x * 0.5f))
		, std::pair(State::Release, std::make_shared<sf::CircleShape>(releaseTexture->getSize().x * 0.5f))
	};
	circleButton[State::Up]->setTexture(upTexture);
	circleButton[State::Over]->setTexture(overTexture);
	circleButton[State::Down]->setTexture(downTexture);
	circleButton[State::Release]->setTexture(releaseTexture);
	initialize();
}

bool CircleButton::containsPoint(const sf::Vector2f & point) const {
	auto circleContains = [&](const std::shared_ptr<const sf::CircleShape> & object) {
		const sf::Vector2f displacement = point - object->getPosition();
		if (pow(displacement.x, 2) + pow(displacement.y, 2) <= pow(object->getRadius(), 2)) {
			return true;
		}
		return false;
	};
	// release state use over state contain point
	State state = currentState == State::Release ? State::Over : currentState;
	return circleContains(circleButton.at(state));
}

void CircleButton::setSpecialEffect(const SpecialEffect effect, const sf::Time & duration) {
	if (effect == SpecialEffect::None) {
		circleButton[State::Release] = nullptr;
		specialDuration = sf::seconds(0);
	}
	else {
		// circleButton[State::Release].reset();
		specialDuration = duration;
	}
	currentEffect = effect;
}

void CircleButton::setSpecialEffectObacity(const sf::Uint8 a) {
	if (!circleButton[State::Release]) return;
	circleButton[State::Release]->setFillColor(sf::Color(sf::Color::White.r, sf::Color::White.b
		, sf::Color::White.g, a));
}

CircleButton::SpecialEffect CircleButton::getSpecialEffect() const {
	return currentEffect;
}

const sf::Time & CircleButton::getDuration() const {
	return specialDuration;
}

CircleButton::~CircleButton() {
}

void CircleButton::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	if (currentState == State::Release) {
		target.draw(*circleButton.at(State::Over), states);
		target.draw(*circleButton.at(currentState), states);
	}
	else {
		target.draw(*circleButton.at(currentState), states);
	}
}

void CircleButton::initialize() {
	addListener(std::make_shared<EventListener<MouseEnteredEvent>>([&] { onMouseEntered(); }));
	addListener(std::make_shared<EventListener<MouseLeftEvent>>([&] { onMouseLeft(); }));
	addListener(std::make_shared<EventListener<MousePressedEvent>>([&](auto & event) { onMousePressed(event); }));
	addListener(std::make_shared<EventListener<MouseReleasedEvent>>([&](auto & event) { onMouseReleased(event); }));
}

void CircleButton::onMouseEntered() {
	if (bReleasing) return;
	currentState = State::Over;
}

void CircleButton::onMouseLeft() {
	if (bReleasing) return;
	currentState = State::Up;
}

void CircleButton::onMousePressed(MousePressedEvent & event) {
	currentState = State::Down;
	// press again will cancel current releasing special effect
	bReleasing = false;
}

void CircleButton::onMouseReleased(MouseReleasedEvent & event) {
	if (circleButton.find(State::Release) != circleButton.end()) {
		if (!bReleasing) {
			bReleasing = true;
			currentState = State::Release;
			clock.restart();
		}
		else if (clock.getElapsedTime() > specialDuration) {
			bReleasing = false;
			currentState = State::Over;
		}
	}
	else {
		currentState = State::Over;
	}
}

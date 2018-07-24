#include "rectButton.h"
#include "../../definition/utility.h"
#include "../../manager/textureManager.h"
#include "../../event/mouse/mouseEvent.h"
#include "../../event/eventListener.h"
#include <SFML/Graphics.hpp>

using namespace game;

std::map<RectButton::Name, RectButton::StateString> RectButton::fileNames({

	});

RectButton::RectButton(const Name name)
	: specialDuration(sf::seconds(0))
	, currentEffect(SpecialEffect::None) {
	auto upTexture = TextureManager::getInstance().get(fileNames[name].buttonUp);
	auto overTexture = TextureManager::getInstance().get(fileNames[name].buttonOver);
	auto downTexture = TextureManager::getInstance().get(fileNames[name].buttonDown);
	rectButton = {
		std::pair(State::Up, std::make_shared<sf::RectangleShape>(sf::Vector2f(upTexture->getSize())))
		, std::pair(State::Over, std::make_shared<sf::RectangleShape>(sf::Vector2f(overTexture->getSize())))
		, std::pair(State::Down, std::make_shared<sf::RectangleShape>(sf::Vector2f(downTexture->getSize())))
		, std::pair(State::Release, nullptr)
	};
	rectButton[State::Up]->setTexture(upTexture);
	rectButton[State::Over]->setTexture(overTexture);
	rectButton[State::Down]->setTexture(downTexture);
	initialize();
}

RectButton::RectButton(const Name name, const SpecialEffect effect, const sf::Time & duration)
	: specialDuration(duration)
	, currentEffect(effect) {
	auto upTexture = TextureManager::getInstance().get(fileNames[name].buttonUp);
	auto overTexture = TextureManager::getInstance().get(fileNames[name].buttonOver);
	auto downTexture = TextureManager::getInstance().get(fileNames[name].buttonDown);
	auto releaseTexture = TextureManager::getInstance().get(fileNames[name].buttonRelease);
	rectButton = {
		std::pair(State::Up, std::make_shared<sf::RectangleShape>(sf::Vector2f(upTexture->getSize())))
		, std::pair(State::Over, std::make_shared<sf::RectangleShape>(sf::Vector2f(overTexture->getSize())))
		, std::pair(State::Down, std::make_shared<sf::RectangleShape>(sf::Vector2f(downTexture->getSize())))
		, std::pair(State::Release, std::make_shared<sf::RectangleShape>(sf::Vector2f(releaseTexture->getSize())))
	};
	rectButton[State::Up]->setTexture(upTexture);
	rectButton[State::Over]->setTexture(overTexture);
	rectButton[State::Down]->setTexture(downTexture);
	rectButton[State::Release]->setTexture(releaseTexture);
	initialize();
}

bool RectButton::containsPoint(const sf::Vector2f & point) const {
	// release state use over state contain point
	State state = currentState == State::Release ? State::Over : currentState;
	return rectButton.at(state)->getGlobalBounds().contains(point);
}

void RectButton::setSpecialEffect(const SpecialEffect effect, const sf::Time & duration) {
	if (effect == SpecialEffect::None) {
		rectButton[State::Release] = nullptr;
		specialDuration = sf::seconds(0);
	}
	else {
		// rectButton[State::Release].reset();
		specialDuration = duration;
	}
	currentEffect = effect;
}

void RectButton::setSpecialEffectObacity(const sf::Uint8 a) {
	if (!rectButton[State::Release]) return;
	rectButton[State::Release]->setFillColor(sf::Color(sf::Color::White.r, sf::Color::White.b
		, sf::Color::White.g, a));
}

RectButton::SpecialEffect RectButton::getSpecialEffect() const {
	return currentEffect;
}

const sf::Time & RectButton::getDuration() const {
	return specialDuration;
}

RectButton::~RectButton() {
}

void RectButton::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	if (currentState == State::Release) {
		target.draw(*rectButton.at(State::Over), states);
		target.draw(*rectButton.at(currentState), states);
	}
	else {
		target.draw(*rectButton.at(currentState), states);
	}
}

void RectButton::initialize() {
	addListener(std::make_shared<EventListener<MouseEnteredEvent>>([&] { onMouseEntered(); }));
	addListener(std::make_shared<EventListener<MouseLeftEvent>>([&] { onMouseLeft(); }));
	addListener(std::make_shared<EventListener<MousePressedEvent>>([&](auto & event) { onMousePressed(event); }));
	addListener(std::make_shared<EventListener<MouseReleasedEvent>>([&](auto & event) { onMouseReleased(event); }));
}

void RectButton::onMouseEntered() {
	if (bReleasing) return;
	currentState = State::Over;
}

void RectButton::onMouseLeft() {
	if (bReleasing) return;
	currentState = State::Up;
}

void RectButton::onMousePressed(MousePressedEvent & event) {
	currentState = State::Down;
	// press again will cancel current releasing special effect
	bReleasing = false;
}

void RectButton::onMouseReleased(MouseReleasedEvent & event) {
	if (rectButton.find(State::Release) != rectButton.end()) {
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

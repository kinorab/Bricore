#include "root.h"
#include "hud.h"
#include "particleSystem.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "handler/mouseHandler.h"
#include "handler/keyboardHandler.h"
#include "event/eventListener.h"

using namespace game;
bool Root::bInstance(false);

Root::Root()
	: hud(new HUD(HUD::BattleArea))
	, mouseLight(new ParticleSystem(2000))
	, mouseHandler(new MouseHandler)
	, keyboardHandler(new KeyboardHandler) {
	assert(!bInstance);
	addChild({ hud, mouseLight });
	addListener(std::make_shared<EventListener<MouseEnteredEvent>>([this]() { onMouseEntered(); }));
	addListener(std::make_shared<EventListener<MouseLeftEvent>>([this]() { onMouseLeft(); }));
	addListener(std::make_shared<EventListener<MouseMovedEvent>>([this](auto & event) { onMouseMoved(event); }));
	addListener(std::make_shared<EventListener<MousePressedEvent>>([this](auto & event) { onMousePressed(event); }));
	addListener(std::make_shared<EventListener<KeyPressedEvent>>([this](auto & event) { onKeyPressed(event); }));
	bInstance = true;
}

bool Root::containsPoint(const sf::Vector2f & point) const {
	return true;
}

void Root::handle(const sf::Event & event) {
	mouseHandler->handle(event, *this);
	keyboardHandler->handle(event, *this);
}

Root::~Root() {
	removeAllChildren();
}

void Root::update(const float updateRatio) {
	mouseLight->update(updateRatio);
}

void Root::onMouseEntered() {
	mouseLight->startEmit();
}

void Root::onMouseLeft() {
	mouseLight->stopEmit();
}

void Root::onMouseMoved(MouseMovedEvent & event) {
	mouseLight->setEmitPosition(sf::Vector2f(static_cast<float>(event.moved.x), static_cast<float>(event.moved.y)));
}

void Root::onMousePressed(MousePressedEvent & event) {

}

void Root::onKeyPressed(KeyPressedEvent & event) {

}

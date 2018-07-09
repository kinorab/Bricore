#include "root.h"
#include "hud.h"
#include "particleSystem.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "event/eventListener.h"
#include "event/SFMLMouseHandler.h"
#include "event/SFMLKeyboardHandler.h"
#include "event/mouse/mouseEvent.h"
#include "event/keyboard/keyEvent.h"

using namespace game;
bool Root::bInstance(false);

Root::Root()
	: hud(new HUD)
	, mouseLight(new ParticleSystem(2000))
	, mouseHandler(new SFMLMouseHandler({ static_cast<int>(GAME_WIDTH), static_cast<int>(GAME_HEIGHT) }))
	, keyboardHandler(new SFMLKeyboardHandler) {
	assert(!bInstance);
	addChild({ hud, mouseLight });
	addListener(std::make_shared<EmptyListener<MouseEnteredEvent>>([this] { onMouseEntered(); }));
	addListener(std::make_shared<EmptyListener<MouseLeftEvent>>([this] { onMouseLeft(); }));
	addListener(std::make_shared<EventListener<MouseMovedEvent>>([this](auto & event) { onMouseMoved(event); }));
	addListener(std::make_shared<EventListener<MousePressedEvent>>([this](auto & event) { onMousePressed(event); }));
	addListener(std::make_shared<EventListener<KeyPressedEvent>>([this](auto & event) { onKeyPressed(event); }));
	bInstance = true;
}

void Root::handle(const sf::Event & event) {
	mouseHandler->handle(event, *this, true);
	keyboardHandler->handle(event, *this);
	Container::handle(event);
}

Root::~Root() {
}

void Root::update(const float updateRatio) {
	Container::update(updateRatio);
}

void Root::onMouseEntered() {
	mouseLight->startEmit();
}

void Root::onMouseLeft() {
	mouseLight->stopEmit();
}

void Root::onMouseMoved(MouseMovedEvent & event) {
	mouseLight->setEmitPosition(sf::Vector2f(static_cast<float>(event.x), static_cast<float>(event.y)));
}

void Root::onMousePressed(MousePressedEvent & event) {

}

void Root::onKeyPressed(KeyPressedEvent & event) {

}

#include "root.h"
#include "hud.h"
#include "graphics.h"
#include "particleSystem.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "handler/handler.h"
#include "event/eventListener.h"
#include <SFML/Graphics.hpp>

using namespace game;
bool Root::bInstance(false);

Root::Root(const std::shared_ptr<Graphics> graph, const std::shared_ptr<const sf::RenderWindow> & window)
	: hud(new HUD(HUD::BattleArea, graph))
	, mouseLight(new ParticleSystem(2000))
	, mouseHandler(new MouseHandler(window))
	, keyboardHandler(new KeyboardHandler)
	, m_graph(std::move(graph)) {
	assert(!bInstance);
	addChild({ std::dynamic_pointer_cast<sf::Drawable>(hud)
		, std::dynamic_pointer_cast<sf::Drawable>(mouseLight) });
	addListener(std::make_shared<EventListener<MouseEnteredEvent>>([this]() { onMouseEntered(); }));
	addListener(std::make_shared<EventListener<MouseLeftEvent>>([this]() { onMouseLeft(); }));
	addListener(std::make_shared<EventListener<MouseMovedEvent>>([this](auto & event) { onMouseMoved(event); }));
	addListener(std::make_shared<EventListener<MousePressedEvent>>([this](auto & event) { onMousePressed(event); }));
	addListener(std::make_shared<EventListener<KeyPressedEvent>>([this](auto & event) { onKeyPressed(event); }));
	addListener(std::make_shared<EventListener<WindowClosedEvent>>([this]() { onWindowClosed(); }));
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
	removeAllListener();
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

void Root::onWindowClosed() {

}

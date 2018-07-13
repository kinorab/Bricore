#include "root.h"
#include "hud.h"
#include "graphics.h"
#include "particleSystem.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "handler/mouseHandler.h"
#include "handler/keyboardHandler.h"
#include "event/eventListener.h"

using namespace game;
bool Root::bInstance(false);

Root::Root(const std::shared_ptr<Graphics> graph)
	: hud(new HUD(HUD::BattleArea, graph))
	, mouseLight(new ParticleSystem(2000))
	, mouseHandler(new MouseHandler)
	, keyboardHandler(new KeyboardHandler)
	, m_graph(std::move(graph)) {
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
	if (event.pressed.button == sf::Mouse::Left) {
		hud->changeGraphicsSetting(GFps::Fps30, GDpi::Low, GAI::None);
	}
	else if (event.pressed.button == sf::Mouse::Right) {
		hud->changeGraphicsSetting(GFps::NoLimit, GDpi::Quality, GAI::Much);
	}
}

void Root::onKeyPressed(KeyPressedEvent & event) {

}

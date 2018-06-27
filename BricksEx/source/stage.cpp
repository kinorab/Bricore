#include "stage.h"
#include "hud.h"
#include "particleSystem.h"
#include "event/mouse/mouseEvent.h"
#include "event/keyboard/keyEvent.h"
#include "event/eventListener.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "manager/audioManager.h"
#include "stuff/obstacle.h"
#include "stuff/ball.h"
#include "stuff/player.h"
#include "stuff/wall.h"

using namespace game;

Stage::Stage() :
	hud(new HUD),
	player(new Player),
	ball(new Ball),
	wall(new Wall),
	obstacle(new Obstacle),
	mouseLight(new ParticleSystem(2000)) {
	// presettle mainBall's position
	ball->followPlayer(player->getTopCenterPos());
	addChild({ hud, player, ball, wall, obstacle, mouseLight });
	using namespace std::placeholders;
	addListener(std::make_shared<EventListener<KeyPressedEvent>>([&](auto & event) { onKeyPressed(event); }));
	addListener(std::make_shared<EventListener<KeyReleasedEvent>>([&](auto & event) { onKeyReleased(event); }));
	addListener(std::make_shared<EmptyListener<MouseEnteredEvent>>([&] { onMouseEntered(); }));
	addListener(std::make_shared<EmptyListener<MouseLeftEvent>>([&] { onMouseLeft(); }));
	addListener(std::make_shared<EventListener<MouseMovedEvent>>([&](auto & event) { onMouseMoved(event); }));
	addListener(std::make_shared<EventListener<MousePressedEvent>>([&](auto & event) { onMousePressed(event); }));
}

Stage::~Stage() {
	AudioManager::getInstance().bgmusic.stop();
	AudioManager::getInstance().sound1.stop();
}

void Stage::update(const float updateRatio) {
	mouseLight->update(updateRatio);
	if (!paused) {
		ball->initializeBall();
		for (size_t i = 0; i < SLICE; ++i) {
			player->update(ball->getMainBallPosition(), ball->getMainBallRadius(), updateRatio);
			if (currentState == GameState::STARTED) {
				wall->update(*ball, updateRatio);
				obstacle->update(*ball, updateRatio);
				ball->update(player->getDP(), player->getSpeed(), updateRatio);
			}
			else {
				ball->followPlayer(player->getTopCenterPos());
				if (game::currentState == GameState::NOT_READY) {
					obstacle->resetPosition();
					game::currentState = GameState::READY;
				}
			}
		}
	}
}

void Stage::onKeyPressed(KeyPressedEvent & event) {
	if (event.code == sf::Keyboard::P) {
		paused = !paused;
		if (paused) {
			dispatchEvent(PausedEvent());
		}
		else {
			dispatchEvent(UnpausedEvent());
		}
		locked = !locked;
	}

	if (locked) {
		return;
	}
	else {
		if (event.code == sf::Keyboard::G) {
			currentState = GameState::STARTED;
		}
	}
}

void Stage::onKeyReleased(KeyReleasedEvent & event) {

}

void Stage::onMouseEntered() {
	mouseLight->startEmit();
}

void Stage::onMouseLeft() {
	mouseLight->stopEmit();
}

void Stage::onMouseMoved(MouseMovedEvent & event) {
	mouseLight->setEmitPosition(sf::Vector2f(static_cast<float>(event.x), static_cast<float>(event.y)));
}

void Stage::onMousePressed(MousePressedEvent & event) {
	if (!locked) {
		if (event.button == sf::Mouse::Left) {
			currentState = GameState::STARTED;
		}
		// debugging feature
		else if (event.button == sf::Mouse::Right) {
			currentState = GameState::NOT_READY;

		}
	}
}
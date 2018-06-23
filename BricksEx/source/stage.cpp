#include "stage.h"
#include "hud.h"
#include "particleSystem.h"
#include "event/mouse/mouseEvent.h"
#include "event/keyboard/keyEvent.h"
#include "event/eventListener.h"
#include "event/emptyListener.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "manager/audioManager.h"
#include "stuff/obstacle.h"
#include "stuff/ball.h"
#include "stuff/player.h"
#include "stuff/brick.h"

namespace game {
	void Stage::PauseEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EmptyListener<PauseEvent> &>(visitor).visit();
	}

	Stage::Stage() :
		hud(new HUD),
		player(new Player),
		ball(new item::Ball),
		brick(new item::Brick),
		obstacle(new Obstacle),
		mouseLight(new ParticleSystem(2000)) {
		// presettle mainBall's position
		ball->followPlayer(player->getMainPlayerTopCenterPos());
		addChild({ hud, player, ball, brick, obstacle, mouseLight });
		addListener(std::make_shared<EventListener<KeyPressedEvent>>([&](auto & event) { onKeyPressed(event); }));
		addListener(std::make_shared<EventListener<KeyReleasedEvent>>([&](auto & event) { onKeyReleased(event); }));
		addListener(std::make_shared<EmptyListener<MouseEnteredEvent>>([&] { onMouseEntered(); }));
		addListener(std::make_shared<EmptyListener<MouseLeftEvent>>([&] { onMouseLeft(); }));
		addListener(std::make_shared<EventListener<MouseMovedEvent>>([&](auto & event) { onMouseMoved(event); }));
		addListener(std::make_shared<EventListener<MousePressedEvent>>([&](auto & event) { onMouseButtonPressed(event); }));
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
				if (GameState::start) {
					brick->update(*ball, updateRatio);
					obstacle->update(*ball, updateRatio);
					ball->update(player->getMainPlayerDP(), updateRatio);
				}
				else {
					ball->followPlayer(player->getMainPlayerTopCenterPos());
					obstacle->restart();
				}
			}
		}
	}

	void Stage::onKeyPressed(KeyPressedEvent & event) {
		if (event.code == sf::Keyboard::P) {
			paused = !paused;
			GameState::lock = !GameState::lock;
		}

		if (GameState::lock) {
			return;
		}
		else {
			if (event.code == sf::Keyboard::G) {
				GameState::start = true;
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

	void Stage::onMouseButtonPressed(MousePressedEvent & event) {
		if (!GameState::lock) {
			if (event.button == sf::Mouse::Left) {
				// debugging feature
				GameState::start = true;
			}
			// debugging feature
			else if (event.button == sf::Mouse::Right) {
				GameState::start = false;
				GameState::ready = false;
			}
		}
	}
}
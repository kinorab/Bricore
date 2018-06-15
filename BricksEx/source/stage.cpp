#include "stage.h"
#include "hud.h"
#include "particleSystem.h"
#include "event/mouseButtonEvent.h"
#include "event/mouseButtonListener.h"
#include "event/mouseMovedEvent.h"
#include "event/mouseMovedListener.h"
#include "event/mouseEnteredEvent.h"
#include "event/mouseEnteredListener.h"
#include "event/mouseLeftEvent.h"
#include "event/mouseLeftListener.h"
#include "event/keyEvent.h"
#include "event/keyListener.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "manager/audioManager.h"
#include "stuff/obstacle.h"
#include "stuff/ball.h"
#include "stuff/player.h"
#include "stuff/brick.h"

Stage::Stage() : 
	hud(new HUD()),
	player(new Player()),
	ball(new item::Ball()),
	brick(new item::Brick()),
	obstacle(new Obstacle()),
	mouseLight(new ParticleSystem(2000)),
	playerPredict(nullptr),
	ballPredict(nullptr),
	brickPredict(nullptr),
	obstaclePredict(nullptr) {
	// settle mainBall's position

	ball->followPlayer(player->getMainPlayerTopCenterPos());
	addChild({ hud, mouseLight });
	using namespace std::placeholders;
	addListener(typeid(game::KeyEvent::Pressed), std::make_shared<game::KeyListener>(std::bind(&Stage::onKeyPressed, this, _1)));
	addListener(typeid(game::KeyEvent::Released), std::make_shared<game::KeyListener>(std::bind(&Stage::onKeyReleased, this, _1)));
	addListener(std::make_shared<game::MouseEnteredListener>(std::bind(&Stage::onMouseEntered, this, _1)));
	addListener(std::make_shared<game::MouseLeftListener>(std::bind(&Stage::onMouseLeft, this, _1)));
	addListener(std::make_shared<game::MouseMovedListener>(std::bind(&Stage::onMouseMoved, this, _1)));
	addListener(typeid(game::MouseButtonEvent::Pressed), std::make_shared<game::MouseButtonListener>(std::bind(&Stage::onMouseButtonPressed, this, _1)));
}

Stage::~Stage() {
	AudioManager::getInstance().bgmusic.stop();
	AudioManager::getInstance().sound1.stop();
}

void Stage::predictUpdate(const float updateSpan) {
	if (playerPredict && ballPredict && brickPredict && obstaclePredict) {
		removeChild({ playerPredict, ballPredict, brickPredict, obstaclePredict });
	}

	playerPredict.reset(new Player(*player));
	ballPredict.reset(new item::Ball(*ball));
	brickPredict.reset(new item::Brick(*brick));
	obstaclePredict.reset(new Obstacle(*obstacle));
	addChildAt({ playerPredict, ballPredict, brickPredict, obstaclePredict }, getChildIndex(hud.get()) + 1);
	if (!GameState::pause) {
		for (size_t i = 0; i < SLICE; ++i) {
			playerPredict->preUpdate(ballPredict->getMainBallPosition(), ballPredict->getMainBallRadius(), updateSpan);
			if (GameState::start) {
				brickPredict->preUpdate(*ballPredict, updateSpan);
				obstaclePredict->preUpdate(*ballPredict, updateSpan);
				ballPredict->preUpdate(playerPredict->getMainPlayerDP(), updateSpan);
			}
			else {
				ballPredict->followPlayer(playerPredict->getMainPlayerTopCenterPos());
			}
		}
	}
}

void Stage::update(const float updateSpan) {
	if (!GameState::pause) {
		ball->initializeBall();
		for (size_t i = 0; i < SLICE; ++i) {
			player->update(ball->getMainBallPosition(), ball->getMainBallRadius());
			if (GameState::start) {
				brick->update(*ball);
				obstacle->update(*ball);
				ball->update(player->getMainPlayerDP());
			}
			else {
				ball->followPlayer(player->getMainPlayerTopCenterPos());
				obstacle->restart();
			}
		}
	}

	mouseLight->update(updateSpan);
}

void Stage::onKeyPressed(game::KeyEvent & event) {
	if (event.code == sf::Keyboard::P) {
		GameState::pause = !GameState::pause;
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

void Stage::onKeyReleased(game::KeyEvent & event) {

}

void Stage::onMouseEntered(game::MouseEnteredEvent &) {
	mouseLight->startEmit();
}

void Stage::onMouseLeft(game::MouseLeftEvent &) {
	mouseLight->stopEmit();
}

void Stage::onMouseMoved(game::MouseMovedEvent & event) {
	mouseLight->setEmitPosition(sf::Vector2f(static_cast<float>(event.x), static_cast<float>(event.y)));
}

void Stage::onMouseButtonPressed(game::MouseButtonEvent & event) {
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


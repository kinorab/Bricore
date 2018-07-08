#include "stage.h"
#include "hud.h"
#include "stuff/stuff.h"
#include "manager/audioManager.h"
#include "gameSys/level/level.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "event/eventListener.h"
#include "event/SFMLMouseHandler.h"
#include "event/SFMLKeyboardHandler.h"
#include "event/mouse/mouseEvent.h"
#include "event/keyboard/keyEvent.h"

using namespace game;

Stage::Stage(const std::shared_ptr<Level> & level)
	: player(new Player)
	, subPlayer(new SubPlayer)
	, ball(new Ball(level))
	, wall(new Wall(level))
	, obstacle(new Obstacle(level))
	, mouseHandler(new SFMLMouseHandler({ static_cast<int>(GAME_WIDTH), static_cast<int>(GAME_HEIGHT) }))
	, keyboardHandler(new SFMLKeyboardHandler) {
	// presettle mainBall's position
	ball->followPlayer(player->getTopCenterPos());
	addChild({ player, ball, wall, obstacle });
	addListener(std::make_shared<EventListener<MousePressedEvent>>([this](auto & event) { onMousePressed(event); }));
	addListener(std::make_shared<EventListener<KeyPressedEvent>>([this](auto & event) { onKeyPressed(event); }));
	addListener(std::make_shared<EventListener<KeyReleasedEvent>>([this](auto & event) { onKeyReleased(event); }));
}

void Stage::handle(const sf::Event & event) {
	mouseHandler->handle(event, *this);
	keyboardHandler->handle(event, *this);
}

Stage::~Stage() {
	AudioManager::getInstance().bgmusic.stop();
	AudioManager::getInstance().sound1.stop();
}

void Stage::update(const float updateRatio) {
	Container::update(updateRatio);
	if (!bPaused) {
		ball->initializeBall();
		for (size_t i = 0; i < SLICE; ++i) {
			player->update(ball->getMainBallPosition(), ball->getMainBallRadius(), updateRatio);
			if (currentState == GameState::NOT_READY) {
				obstacle->resetPosition();
				currentState = GameState::READY;
			}
			if (currentState == GameState::STARTED) {
				wall->update(*ball, updateRatio);
				obstacle->update(*ball, updateRatio);
				ball->update(player->getDP(), player->getSpeed(), updateRatio);
			}
			else {
				ball->followPlayer(player->getTopCenterPos());
			}
		}
	}
}

void Stage::onKeyPressed(KeyPressedEvent & event) {
	if (event.code == sf::Keyboard::P) {
		bPaused = !bPaused;
		if (bPaused) {
			dispatchEvent(PausedEvent());
		}
		else {
			dispatchEvent(UnpausedEvent());
		}
	}

	if (bPaused) return;
	if (event.code == sf::Keyboard::G) {
		currentState = GameState::STARTED;
	}
}

void Stage::onKeyReleased(KeyReleasedEvent & event) {

}

void Stage::onMousePressed(MousePressedEvent & event) {
	if (bPaused) return;
	if (event.button == sf::Mouse::Left) {
		currentState = GameState::STARTED;
	}
	else if (event.button == sf::Mouse::Right) {
		// debugging feature
		currentState = GameState::NOT_READY;
	}
}

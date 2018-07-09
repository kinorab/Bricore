#include "stage.h"
#include "hud.h"
#include "root.h"
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

bool Stage::bInstance(false);

Stage::Stage(const std::shared_ptr<Level> & level, const std::shared_ptr<const Root> root)
	: player(new Player(level))
	, subPlayer(new SubPlayer(level))
	, ball(new Ball(level))
	, wall(new Wall(level))
	, obstacle(new Obstacle(level))
	, mouseHandler(new SFMLMouseHandler({ static_cast<int>(GAME_WIDTH), static_cast<int>(GAME_HEIGHT) }))
	, keyboardHandler(new SFMLKeyboardHandler)
	, c_root(std::move(root))
	, key({ sf::Keyboard::Key::P, sf::Keyboard::Key::Escape }) {
	assert(!bInstance);
	resetChildrenCopyTarget();
	addChild({ c_root->getChildAt(0), player, ball, wall, obstacle, c_root->getChildAt(1) });
	addListener(std::make_shared<EventListener<MousePressedEvent>>([this](auto & event) { onMousePressed(event); }));
	addListener(std::make_shared<EventListener<KeyPressedEvent>>([this](auto & event) { onKeyPressed(event); }));
	addListener(std::make_shared<EventListener<KeyReleasedEvent>>([this](auto & event) { onKeyReleased(event); }));
	bInstance = true;
}

void Stage::resetChildrenCopyTarget() {
	assert(player && subPlayer && ball && wall && obstacle);
	player->resetCopyTarget(subPlayer, ball);
	subPlayer->resetCopyTarget(player, ball);
	ball->resetCopyTarget(player, subPlayer);
	wall->resetCopyTarget(ball);
	obstacle->resetCopyTarget(subPlayer, ball);
}

void Stage::resetKey(const sf::Keyboard::Key pause, const sf::Keyboard::Key menu) {
	key = { pause, menu };
}

void Stage::handle(const sf::Event & event) {
	mouseHandler->handle(event, *this, true);
	keyboardHandler->handle(event, *this);
	Container::handle(event);
}

Stage::~Stage() {
	AudioManager::getInstance().bgmusic.stop();
	AudioManager::getInstance().sound1.stop();
}

void Stage::update(const float updateRatio) {
	if (!bPaused) {
		ball->initializeBall();
		for (size_t i = 0; i < SLICE; ++i) {
			player->tryUpdate(updateRatio);
			if (currentState == GameState::NOT_READY) {
				obstacle->resetPosition();
				currentState = GameState::READY;
			}
			if (currentState == GameState::STARTED) {
				wall->tryUpdate(updateRatio);
				obstacle->tryUpdate(updateRatio);
				ball->tryUpdate(updateRatio);
			}
			else {
				ball->followPlayer();
			}
		}
	}
}

void Stage::onKeyPressed(KeyPressedEvent & event) {
	if (event.code == key.pause) {
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

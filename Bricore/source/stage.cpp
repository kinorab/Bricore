#include "stage.h"
#include "hud.h"
#include "root.h"
#include "stuff/stuff.h"
#include "manager/audioManager.h"
#include "gameSys/level/level.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "handler/mouseHandler.h"
#include "handler/keyboardHandler.h"
#include "event/eventListener.h"
#include "event/game/gameEvent.h"
#include <SFML/Graphics.hpp>

using namespace game;

bool Stage::bInstance(false);

Stage::Stage(const std::shared_ptr<Level> & level, const std::shared_ptr<const Root> root)
	: player(new Player(level))
	, subPlayer(new SubPlayer(level))
	, ball(new Ball(level))
	, wall(new Wall(level))
	, obstacle(new Obstacle(level))
	, key({ sf::Keyboard::Key::P, sf::Keyboard::Key::Escape })
	, mouseHandler(new MouseHandler)
	, keyboardHandler(new KeyboardHandler)
	, c_root(std::move(root))
	, m_level(level) {
	assert(!bInstance);
	resetChildrenCopyTarget();
	addChild({ player, subPlayer, ball, wall, obstacle });
	addListener(std::make_shared<EventListener<MousePressedEvent>>([this](auto & event) { onMousePressed(event); }));
	addListener(std::make_shared<EventListener<KeyPressedEvent>>([this](auto & event) { onKeyPressed(event); }));
	addListener(std::make_shared<EventListener<KeyReleasedEvent>>([this](auto & event) { onKeyReleased(event); }));
	bInstance = true;
}

bool Stage::containsPoint(const sf::Vector2f & point) const {
	return true;
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
	mouseHandler->handle(event, *this);
	keyboardHandler->handle(event, *this);
}

Stage::~Stage() {
	removeAllChildren();
	AudioManager::getInstance().getMusic("bg")->stop();
	AudioManager::getInstance().getSound("hitBoard")->stop();
}

void Stage::update(const float updateRatio) {
	if (!bPaused) {
		ball->initializeBall();
		for (size_t i = 0; i < SLICE; ++i) {
			player->update(updateRatio);
			subPlayer->update(updateRatio);
			if (currentGameState == GameState::NOT_READY) {
				obstacle->resetPosition();
				currentGameState = GameState::READY;
			}
			if (currentGameState == GameState::STARTED) {
				wall->update(updateRatio);
				obstacle->update(updateRatio);
				ball->update(updateRatio);
			}
			else {
				ball->followPlayer();
			}
		}
	}
}

void Stage::onKeyPressed(KeyPressedEvent & event) {
	if (event.pressed.code == key.pause) {
		bPaused = !bPaused;
		if (bPaused) {
			dispatchEvent(GamePausedEvent());
		}
		else {
			dispatchEvent(GameUnpausedEvent());
		}
	}

	if (bPaused) return;
	if (event.pressed.code == sf::Keyboard::G) {
		currentGameState = GameState::STARTED;
	}
}

void Stage::onKeyReleased(KeyReleasedEvent & event) {

}

void Stage::onMousePressed(MousePressedEvent & event) {
	if (bPaused) return;
	if (event.pressed.button == sf::Mouse::Left) {
		currentGameState = GameState::STARTED;
	}
	else if (event.pressed.button == sf::Mouse::Right) {
		// debugging feature
		currentGameState = GameState::NOT_READY;
	}
}

void Stage::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(*c_root->getChildAt(0), states);
	Container::draw(target, states);
	target.draw(*c_root->getChildAt(1), states);
}

#include "stage.h"
#include "hud.h"
#include "root.h"
#include "stuff/stuff.h"
#include "manager/audioManager.h"
#include "gameSys/level/level.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "handler/handler.h"
#include "event/eventListener.h"
#include "event/game/gameEvent.h"
#include <SFML/Graphics.hpp>

using namespace game;

bool Stage::bInstance(false);

Stage::Stage(const std::shared_ptr<Level> level, const std::shared_ptr<const Root> root
	, const std::shared_ptr<const sf::RenderWindow> & window)
	: player(new Player(level))
	, subPlayer(new SubPlayer(level))
	, ball(new Ball(level))
	, wall(new Wall(level))
	, obstacle(new Obstacle(level))
	, key({ sf::Keyboard::P, sf::Keyboard::Escape })
	, gameStateEvent(new GameStateEvent)
	, mouseHandler(new MouseHandler(window))
	, keyboardHandler(new KeyboardHandler)
	, gameHandler(new GameHandler)
	, tempType()
	, c_root(std::move(root))
	, m_level(std::move(level)) {
	assert(!bInstance);
	gameStateEvent->type = GameStateEvent::GameReady;
	resetChildrenCopyTarget();
	addChild({ std::dynamic_pointer_cast<sf::Drawable>(obstacle)
		, std::dynamic_pointer_cast<sf::Drawable>(wall)
		, std::dynamic_pointer_cast<sf::Drawable>(player)
		, std::dynamic_pointer_cast<sf::Drawable>(subPlayer)
		, std::dynamic_pointer_cast<sf::Drawable>(ball) });
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
	mouseHandler->handle(event, *this);
	keyboardHandler->handle(event, *this);
}

Stage::~Stage() {
	removeAllChildren();
	removeAllListener();
	AudioManager::getInstance().getMusic("bg")->stop();
	AudioManager::getInstance().getSound("hitBoard")->stop();
}

void Stage::update(const float updateRatio) {
	updateGameStateEvent();
	if (gameStateEvent->type != GameStateEvent::GamePaused && gameStateEvent->type != GameStateEvent::GameResumed) {
		ball->initializeBall();
		for (size_t i = 0; i < SLICE; ++i) {
			player->update(updateRatio);
			subPlayer->update(updateRatio);
			if (gameStateEvent->type == GameStateEvent::GameStarted) {
				wall->update(updateRatio);
				obstacle->update(updateRatio);
				ball->update(updateRatio);
			}
		}
	}
	// temp setting
	if (gameStateEvent->type == GameStateEvent::GameFinishedLevel) {
		gameStateEvent->type = GameStateEvent::GameReady;
	}
}

void Stage::updateGameStateEvent() {
	// to ready state
	if (ball->isMainBallBroken()) {
		gameStateEvent->type = GameStateEvent::GameReady;
	}
	// to finish state
	if (wall->isEmpty()) {
		m_level->finishLevel();
		gameStateEvent->type = GameStateEvent::GameFinishedLevel;
		gameStateEvent->finishedLevel.uLevel = m_level->getcurrentLevel();
	}
	// back to start / ready state
	if (gameStateEvent->type == GameStateEvent::GameResumed) {
		if (gameStateEvent->resumed.fCountDown <= 0.0f) {
			gameStateEvent->type = tempType;
		}
	}
	gameHandler->handler(*gameStateEvent, *this);
}

void Stage::onKeyPressed(KeyPressedEvent & event) {
	dispatchAllChildrenEvent(event);
	if (gameStateEvent->type == GameStateEvent::GameFinishedLevel
		|| gameStateEvent->type == GameStateEvent::GameOver) return;
	if (event.pressed.code == key.pause) {
		if (gameStateEvent->type == GameStateEvent::GamePaused) {
			gameStateEvent->type = GameStateEvent::GameResumed;
			// resume from prepare area no countDown
			if (tempType != GameStateEvent::GamePrepared) {
				gameStateEvent->resumed.fCountDown = 3.f;
			}
		}
		else if (gameStateEvent->type != GameStateEvent::GameResumed) {
			tempType = gameStateEvent->type;
			gameStateEvent->type = GameStateEvent::GamePaused;
			++gameStateEvent->paused.uPausedTimes;
		}
	}

	if (gameStateEvent->type == GameStateEvent::GamePaused) return;
	if (event.pressed.code == sf::Keyboard::G) {
		gameStateEvent->type = GameStateEvent::GameStarted;
	}
}

void Stage::onKeyReleased(KeyReleasedEvent & event) {
	dispatchAllChildrenEvent(event);
	if (gameStateEvent->type == GameStateEvent::GameFinishedLevel) return;
}

void Stage::onMousePressed(MousePressedEvent & event) {
	if (gameStateEvent->type == GameStateEvent::GamePaused 
		|| gameStateEvent->type == GameStateEvent::GameResumed
		|| gameStateEvent->type == GameStateEvent::GameFinishedLevel) return;
	if (event.pressed.button == sf::Mouse::Left) {
		if (ball->containsPoint(sf::Vector2f(sf::Vector2i(event.pressed.x, event.pressed.y)))) {
			gameStateEvent->type = GameStateEvent::GameStarted;
		}
	}
	else if (event.pressed.button == sf::Mouse::Right) {
		// debugging feature
		gameStateEvent->type = GameStateEvent::GameReady;
	}
}

void Stage::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (gameStateEvent->type == GameStateEvent::GameFinishedLevel) return;
	target.draw(*c_root->getChildAt(0), states);
	Container::draw(target, states);
	target.draw(*c_root->getChildAt(1), states);
}

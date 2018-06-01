#include "stage.h"
#include "hud.h"
#include "particleSystem.h"
#include "event/event.h"
#include "definition/define.h"
#include "manager/audioManager.h"
#include "stuff/obstacle.h"
#include "stuff/ball.h"
#include "stuff/player.h"
#include "stuff/brick.h"

bool Stage::instantiated = false;

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
	// presettle mainBall's position
	if (getInstantiated()) {
		throw std::invalid_argument("This class can only be instantiated once!");
	}

	ball->followPlayer(player->getMainPlayerTopCenterPos());
	addChild({ hud, mouseLight });
	using namespace std::placeholders;
	addEventListener(game::EventType::KeyPressed, std::bind(&Stage::onKeyPressed, this, _1));
	addEventListener(game::EventType::KeyReleased, std::bind(&Stage::onKeyReleased, this, _1));
	addEventListener(game::EventType::MouseEntered, std::bind(&Stage::onMouseEntered, this, _1));
	addEventListener(game::EventType::MouseLeft, std::bind(&Stage::onMouseLeft, this, _1));
	addEventListener(game::EventType::MouseMoved, std::bind(&Stage::onMouseMoved, this, _1));
	addEventListener(game::EventType::MouseButtonPressed, std::bind(&Stage::onMouseButtonPressed, this, _1));
	setInstantiated(true);
}

Stage::~Stage() {
	AudioManager::getInstance()->bgmusic.stop();
	AudioManager::getInstance()->sound1.stop();
	setInstantiated(false);
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

bool Stage::getInstantiated() const {
	return Stage::instantiated;
}

void Stage::setInstantiated(bool value) {
	Stage::instantiated = value;
}

void Stage::onKeyPressed(game::Event * event) {
	if (std::get<sf::Event::KeyEvent>(event->data).code == sf::Keyboard::P) {
		GameState::pause = !GameState::pause;
		GameState::lock = !GameState::lock;
	}

	if (GameState::lock) {
		return;
	}
	else {
		if (std::get<sf::Event::KeyEvent>(event->data).code == sf::Keyboard::G) {
			GameState::start = true;
		}
	}
}

void Stage::onKeyReleased(game::Event * event) {

}

void Stage::onMouseEntered(game::Event *) {
	GameState::light = true;
}

void Stage::onMouseLeft(game::Event *) {
	GameState::light = false;
}

void Stage::onMouseMoved(game::Event * event) {
	auto moveEvent = std::get<sf::Event::MouseMoveEvent>(event->data);
	mouseLight->setEmitPosition(sf::Vector2f(static_cast<float>(moveEvent.x), static_cast<float>(moveEvent.y)));
}

void Stage::onMouseButtonPressed(game::Event * event) {
	if (!GameState::lock) {
		if (std::get<sf::Event::MouseButtonEvent>(event->data).button == sf::Mouse::Left) {
			// debugging feature
			GameState::start = true;
		}
		// debugging feature
		else if (std::get<sf::Event::MouseButtonEvent>(event->data).button == sf::Mouse::Right) {
			GameState::start = false;
			GameState::ready = false;
		}
	}
}


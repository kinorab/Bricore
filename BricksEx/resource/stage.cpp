#include "stage.h"
#include "hud.h"
#include "particleSystem.h"
#include "definition/define.h"
#include "manager/audioManager.h"
#include "stuff/obstacle.h"
#include "stuff/ball.h"
#include "stuff/player.h"
#include "stuff/brick.h"

std::shared_ptr<Stage> Stage::instance = nullptr;

std::shared_ptr<Stage> Stage::getInstance() {
	if (!instance) {
		instance.reset(new Stage());
	}

	return instance;
}

bool Stage::resetInstance() {
	if (instance) {
		instance.reset();
		return true;
	}
	return false;
}

void Stage::predictUpdate(const float intervalTime) {
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
			playerPredict->preUpdate(ballPredict->getMainBallPosition(), ballPredict->getMainBallRadius(), intervalTime);
			if (GameState::start) {
				brickPredict->preUpdate(*ballPredict, intervalTime);
				obstaclePredict->preUpdate(*ballPredict, intervalTime);
				ballPredict->preUpdate(playerPredict->getMainPlayerDP(), intervalTime);
			}
			else {
				ballPredict->followPlayer(playerPredict->getMainPlayerTopCenterPos());
			}
		}
	}
}

Stage::~Stage() {
	AudioManager::getInstance()->bgmusic.stop();
	AudioManager::getInstance()->sound1.stop();
}

void Stage::update(float updateSpan, sf::Vector2f mousePosition) {
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
	mouseLight->setEmitPosition(mousePosition);
	mouseLight->update(updateSpan);
}

Stage::Stage()
	: hud(new HUD())
	, player(new Player())
	, ball(new item::Ball())
	, brick(new item::Brick())
	, obstacle(new Obstacle())
	, mouseLight(new ParticleSystem(2000))
	, playerPredict(nullptr)
	, ballPredict(nullptr)
	, brickPredict(nullptr)
	, obstaclePredict(nullptr) {
	// presettle mainBall's position
	ball->followPlayer(player->getMainPlayerTopCenterPos());
	addChild({ hud, mouseLight });
	using namespace std::placeholders;
	addEventListener(sf::Event::KeyPressed, std::bind(&Stage::onKeyPressed, this, _1));
	addEventListener(sf::Event::KeyReleased, std::bind(&Stage::onKeyReleased, this, _1));
	addEventListener(sf::Event::MouseEntered, std::bind(&Stage::onMouseEntered, this, _1));
	addEventListener(sf::Event::MouseLeft, std::bind(&Stage::onMouseLeft, this, _1));
	addEventListener(sf::Event::MouseButtonPressed, std::bind(&Stage::onMouseButtonPressed, this, _1));
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

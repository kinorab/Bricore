#include "stage.h"
#include "define.h"
#include "audio.h"
#include "hud.h"
#include "particleSystem.h"
#include "obstacle.h"
#include "ball.h"
#include "player.h"
#include "brick.h"
#include "levelDeploy.h"
#include <atomic>
#include <iostream>

std::shared_ptr<ParticleSystem> Stage::mouseLight(new ParticleSystem(2000));
std::shared_ptr<Stage> Stage::instance = nullptr;
std::mutex Stage::mutex;

std::shared_ptr<Stage> Stage::getInstance() {
	std::shared_ptr<Stage> stagePtr = std::atomic_load_explicit(&instance, std::memory_order_acquire);
	if (!stagePtr) {
		// prevent multithread get instance concurrently
		std::lock_guard<std::mutex> lock(mutex);
		stagePtr = std::atomic_load_explicit(&instance, std::memory_order_relaxed);
		if (!stagePtr) {
			stagePtr = std::shared_ptr<Stage>(new Stage());
			using namespace std::placeholders;
			stagePtr->addEventListener(sf::Event::KeyPressed, std::bind(&Stage::onKeyPressed, stagePtr.get(), _1));
			stagePtr->addEventListener(sf::Event::KeyReleased, std::bind(&Stage::onKeyReleased, stagePtr.get(), _1));
			stagePtr->addEventListener(sf::Event::MouseEntered, std::bind(&Stage::onMouseEntered, stagePtr.get(), _1));
			stagePtr->addEventListener(sf::Event::MouseLeft, std::bind(&Stage::onMouseLeft, stagePtr.get(), _1));
			stagePtr->addEventListener(sf::Event::MouseButtonPressed, std::bind(&Stage::onMouseButtonPressed, stagePtr.get(), _1));
			stagePtr->initialize();
			std::atomic_store_explicit(&instance, stagePtr, std::memory_order_release);
		}
	}
	return stagePtr;
}

Stage::~Stage() {
	Audio::bgmusic.stop();
	Audio::sound1.stop();
}

void Stage::update(float updateSpan, sf::Vector2f mousePosition) {

	if (!GameState::pause) {
		item::Ball::initializeBall();
		for (size_t i = 0; i < SLICE; ++i) {
			Player::playerMove(Audio::sound1, item::Ball::getMainBallPosition(), item::Ball::getMainBallRadius());
			if (GameState::start) {
				item::Brick::update();
				Obstacle::update();
				item::Ball::update(Player::getMainPlayerDP());
			}
			else {
				item::Ball::followPlayer(Player::getMainPlayerTopCenterPos());
				Obstacle::restart();
			}
		}
	}

	mouseLight->setEmitPosition(mousePosition);
	mouseLight->update(updateSpan);
}

Stage::Stage() {
	addChild({ HUD::getInstance(), Player::getInstance(), item::Ball::getInstance(), item::Brick::getInstance(), Obstacle::getInstance(), mouseLight });
	HUD::setBackgroundColor(sf::Color(210, 210, 210));
	item::Ball::followPlayer(Player::getMainPlayerTopCenterPos());
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

void Stage::onKeyReleased(game::Event * event){

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

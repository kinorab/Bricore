#include "stage.h"
#include "define.h"
#include "audio.h"
#include "hud.h"
#include "particleSystem.h"
#include "obstacle.h"
#include "ball.h"
#include "player.h"
#include "brick.h"
#include "LVDeploy.h"
#include <atomic>
#include <iostream>

std::shared_ptr<Stage> Stage::instance = nullptr;

std::shared_ptr<Stage> Stage::getInstance() {
	if (!instance) {
		instance = std::shared_ptr<Stage>(new Stage());
		using namespace std::placeholders;
		instance->addEventListener(sf::Event::KeyPressed, std::bind(&Stage::onKeyPressed, instance.get(), _1));
		instance->addEventListener(sf::Event::KeyReleased, std::bind(&Stage::onKeyReleased, instance.get(), _1));
		instance->addEventListener(sf::Event::MouseEntered, std::bind(&Stage::onMouseEntered, instance.get(), _1));
		instance->addEventListener(sf::Event::MouseLeft, std::bind(&Stage::onMouseLeft, instance.get(), _1));
		instance->addEventListener(sf::Event::MouseButtonPressed, std::bind(&Stage::onMouseButtonPressed, instance.get(), _1));
		instance->initialize();
	}
	return instance;
}

std::shared_ptr<Stage> Stage::getPredictInstance() {
	static std::shared_ptr<Stage> preInstance;
	static Stage predict;
	if (instance) {
		predict = *instance;
		predict.update();
		preInstance = std::make_shared<Stage>(predict);
		return preInstance;
	}
	return nullptr;
}

bool Stage::resetInstance() {
	if (instance) {
		instance.reset();
		return true;
	}
	return false;
}

Stage::~Stage() {
	Audio::bgmusic.stop();
	Audio::sound1.stop();
}

void Stage::update() {

	if (!GameState::pause) {
		item::Ball::getInstance()->initializeBall();
		for (size_t i = 0; i < SLICE; ++i) {
			Player::getInstance()->update();
			if (GameState::start) {
				item::Brick::getInstance()->update();
				Obstacle::getInstance()->update();
				item::Ball::getInstance()->update();
			}
			else {
				item::Ball::getInstance()->followPlayer();
				Obstacle::getInstance()->restart();
			}
		}
	}

}

void Stage::updateMouseLight(float updateSpan, sf::Vector2f mousePosition) {
	mouseLight->setEmitPosition(mousePosition);
	mouseLight->update(updateSpan);
}

Stage::Stage() {
	addChild({ HUD::getInstance(), Player::getInstance(), item::Ball::getInstance(), item::Brick::getInstance(), Obstacle::getInstance()});
	mouseLight = std::shared_ptr<ParticleSystem>(new ParticleSystem(2000));
	addChild({ mouseLight });
}

Stage & Stage::operator=(const Stage &) = default;

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


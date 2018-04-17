#include "stage.h"
#include "audio.h"
#include "levelDeploy.h"
#include <iostream>

std::shared_ptr<item::Ball> Stage::ball(new item::Ball());
std::shared_ptr<item::Brick> Stage::bricks(new item::Brick());
std::shared_ptr<HUD> Stage::hud(new HUD());
std::shared_ptr<ParticleSystem> Stage::mouseLight(new ParticleSystem(2000));
std::shared_ptr<Player> Stage::player(new Player());
std::shared_ptr<Obstacle> Stage::obstacles(new Obstacle());

Stage::Stage() {
	/*
	Audio::bgmusic.play();
	Audio::bgmusic.setLoop(true);
	*/
	HUD::setBackgroundColor(sf::Color(210, 210, 210));
	item::Ball::followPlayer(player->getMainPlayerTopCenterPos());
	addChild({ hud, obstacles, player, ball, bricks, mouseLight });
	using namespace std::placeholders;
	addEventListener(sf::Event::KeyPressed, std::bind(&Stage::onKeyPressed, this, _1));
	addEventListener(sf::Event::KeyReleased, std::bind(&Stage::onKeyReleased, this, _1));
	addEventListener(sf::Event::MouseEntered, std::bind(&Stage::onMouseEntered, this, _1));
	addEventListener(sf::Event::MouseLeft, std::bind(&Stage::onMouseLeft, this, _1));
	addEventListener(sf::Event::MouseButtonPressed, std::bind(&Stage::onMouseButtonPressed, this, _1));
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
			GameState::start = true;
		}
		// debugging feature
		else if (std::get<sf::Event::MouseButtonEvent>(event->data).button == sf::Mouse::Right) {
			GameState::start = false;
			GameState::ready = false;
		}
	}
}

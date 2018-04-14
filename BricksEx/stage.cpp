#include "stage.h"
#include "audio.h"
#include "levelDeploy.h"
#include <iostream>

float Stage::blockLength(100.f);
float Stage::incre1(3.f);
std::shared_ptr<item::Ball> Stage::ball(new item::Ball());
std::shared_ptr<item::Brick> Stage::bricks(new item::Brick(LVDeploy::getLevel(), 60.f, 25.f, sf::Vector2f(1.f, 2.f), 3.f, 5.f));
std::shared_ptr<HUD> Stage::hud(new HUD());
std::shared_ptr<ParticleSystem> Stage::mouseLight(new ParticleSystem(2000));
std::shared_ptr<Player> Stage::player(new Player());
std::shared_ptr<Obstacle> Stage::obstacles(new Obstacle(
	{ sf::Vector2f(blockLength, blockLength * incre1)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.75f)
	, sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1 * 1.75f)
	, sf::Vector2f((LEVEL_WIDTH - blockLength) / 2 , (LEVEL_HEIGHT - blockLength * incre1) / 2) }
	, { sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 0.5f)
	, sf::Vector2f(blockLength, blockLength * incre1 * 1.25f) }));

Stage::Stage() {
	/*
	Audio::bgmusic.play();
	Audio::bgmusic.setLoop(true);
	*/
	HUD::setBackgroundColor(sf::Color(210, 210, 210));
	item::Ball::followPlayer(player->getMainPlayerTopCenterPos());
	Obstacle::setBlockColor(0, sf::Color::Black, sf::Color::Blue, sf::Color::Black, sf::Color::Black);
	Obstacle::setBlockColor(1, sf::Color::Green, sf::Color::Black, sf::Color::Cyan, sf::Color::Black);
	Obstacle::setBlockColor(2, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan);
	Obstacle::setBlockColor(3, sf::Color::Magenta, sf::Color::Black, sf::Color::Red, sf::Color::White);
	Obstacle::setBlockColor(4, sf::Color::White, sf::Color::Black, sf::Color::White, sf::Color::Black);
	Obstacle::setBlockSpeed(0, 1.5f);
	Obstacle::setBlockSpeed(1, -1.5f);
	Obstacle::setBlockSpeed(2, 2.5f);
	Obstacle::setBlockSpeed(3, -2.5f);
	Obstacle::setBlockSpeed(4, 3.f);
	item::Brick::setBrickColor(sf::Color(255, 183, 197));
	addChild({ hud, obstacles, player, ball, bricks, mouseLight });
	addEventListener(sf::Event::MouseEntered, std::bind(&Stage::onMouseEntered, this, std::placeholders::_1));
	addEventListener(sf::Event::MouseLeft, std::bind(&Stage::onMouseLeft, this, std::placeholders::_1));
	addEventListener(sf::Event::MouseButtonPressed, std::bind(&Stage::onMousePressed, this, std::placeholders::_1));
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

void Stage::onMouseEntered(game::Event * event) {
	GameState::light = true;
}

void Stage::onMouseLeft(game::Event * event) {
	GameState::light = false;
}

void Stage::onMousePressed(game::Event * event) {
	if (!GameState::lock) {
		if (event->mouseButton.button == sf::Mouse::Left) {
			GameState::start = true;
		}
		// debugging feature
		else if (event->mouseButton.button == sf::Mouse::Right) {
			GameState::start = false;
			GameState::ready = false;
		}
	}
}

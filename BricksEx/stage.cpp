#include "stage.h"
#include "audio.h"
#include <iostream>

float Stage::blockLength(100.f);
float Stage::incre1(3.f);
std::shared_ptr<item::Ball> Stage::ball(new item::Ball());
std::shared_ptr<item::Brick> Stage::bricks(new item::Brick(level, 60.f, 25.f, sf::Vector2f(1.f, 2.f), 3.f, 5.f));
std::shared_ptr<HUD> Stage::hud(new HUD());
std::shared_ptr<ParticleSystem> Stage::mouseLight(new ParticleSystem(2000));
std::shared_ptr<Obstacle> Stage::obstacles(new Obstacle(2
	, { sf::Vector2f(blockLength, blockLength * incre1), sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1) }
, { sf::Vector2f(blockLength, blockLength * incre1), sf::Vector2f(blockLength, blockLength * incre1) }));
std::shared_ptr<Player> Stage::player(new Player());

Stage::Stage() {
	/*
	Audio::bgmusic.play();
	Audio::bgmusic.setLoop(true);
	*/
	HUD::setBackgroundColor(sf::Color(210, 210, 210));
	item::Ball::followPlayer(player->getMainPlayerTopCenterPos());
	Obstacle::setBlockColor(0, sf::Color::Black, sf::Color::Blue, sf::Color::Black, sf::Color::Black);
	Obstacle::setBlockColor(1, sf::Color::Green, sf::Color::Black, sf::Color::Cyan, sf::Color::Black);
	Obstacle::setBlockSpeed(0, 1.5f);
	Obstacle::setBlockSpeed(1, -1.5f);
	item::Brick::setBrickColor(sf::Color(255, 183, 197));
	addChild({ hud, obstacles, player, ball, bricks, mouseLight });
	addEventListener("SomeEvent",
		[this](game::Event * event) {
		std::cout << "Stage:" << event->getType() << std::endl;
	});
	hud->addEventListener("SomeEvent",
		[this](game::Event * event) {
		std::cout << "HUD:" << event->getType() << std::endl;
	});
}

Stage::~Stage() {
	Audio::bgmusic.stop();
	Audio::sound1.stop();
}

void Stage::initialize() {
	Container::initialize();
	hud->dispatchEvent(new game::Event("SomeEvent"));
}

void Stage::update(float updateSpan, sf::Vector2f mousePosition) {

	if (!GameState::pause) {
		item::Ball::initializeBall();
		for (size_t i = 0; i < SLICE; ++i) {
			Player::playerMove(Audio::sound1, item::Ball::getMainBallPosition(), item::Ball::getMainBallRadius());
			if (GameState::start) {
				Obstacle::update();
				item::Brick::update();
				item::Ball::update(Player::getMainPlayerDP());
			}
			else {
				item::Ball::followPlayer(Player::getMainPlayerTopCenterPos());
				Obstacle::reset();
			}
		}
	}

	mouseLight->setEmitPosition(mousePosition);
	mouseLight->update(updateSpan);
}
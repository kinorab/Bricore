#include "stage.h"
#include "audio.h"
#include <iostream>

Stage::Stage()
	: background(new game::DisplayObject<sf::RectangleShape>(sf::Vector2f(GAME_WIDTH, GAME_HEIGHT))),
	blockLength(100.f),
	incre1(3.f),
	obstacles(new Obstacle(2
		, { sf::Vector2f(blockLength, blockLength * incre1), sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1) }
		, { sf::Vector2f(blockLength, blockLength * incre1), sf::Vector2f(blockLength, blockLength * incre1) })),
	player(new Player(5.5f)),
	ball(new item::Ball()),
	bricks(new item::Brick(1, 60.f, 25.f, sf::Vector2f(1.f, 2.f), 3.f, 5.f)),
	hud(new HUD()),
	mouseLight(new ParticleSystem(2000)) {
	/*
	Audio::bgmusic.play();
	Audio::bgmusic.setLoop(true);
	*/
	background->setFillColor(sf::Color(210, 210, 210));
	ball->followPlayer(player->getMainPlayerTopCenterPos());
	obstacles->setBlockColor(0, sf::Color::Black, sf::Color::Blue, sf::Color::Black, sf::Color::Black);
	obstacles->setBlockColor(1, sf::Color::Green, sf::Color::Black, sf::Color::Cyan, sf::Color::Black);
	obstacles->setBlockSpeed(0, 1.5f);
	obstacles->setBlockSpeed(1, -1.5f);
	bricks->setBrickColor(sf::Color(255, 183, 197));
	addChild({ background, hud, obstacles, player, ball, bricks, mouseLight });
}

Stage::~Stage() {
	Audio::bgmusic.stop();
	Audio::sound1.stop();
}

void Stage::update(float updateSpan, sf::Vector2f mousePosition) {

	if (!GameState::pause) {
		player->playerMove(Audio::sound1, ball->getMainBallBounds(), ball->getMainBallPosition());
		ball->initializeBall(player->getMainPlayerBounds(), player->getMainPlayerPos());
		if (GameState::start) {
			obstacles->update(*ball);
			bricks->update(*ball);
			ball->update(player->getMainPlayerBounds(), player->getMainPlayerPos());
		}
		else {
			ball->followPlayer(player->getMainPlayerTopCenterPos());
			obstacles->reset();
		}
	}
	mouseLight->setEmitPosition(mousePosition);
	mouseLight->update(updateSpan);
}
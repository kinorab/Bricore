#include "stage.h"
#include "audio.h"
#include <iostream>

Stage::Stage(sf::RenderWindow & window)
	:window(window),
	blockLength(100.f),
	incre1(3.f),
	obstacles(new Obstacle(2
		, { sf::Vector2f(blockLength, blockLength * incre1), sf::Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1) }
	, { sf::Vector2f(blockLength, blockLength * incre1), sf::Vector2f(blockLength, blockLength * incre1) })),
	player(new Player(5.5f)),
	ball(new item::Ball()),
	bricks(new item::Brick(1, 60.f, 25.f, sf::Vector2f(0.8f, 2.f), 3.f)),
	hud(new HUD()),
	mouseLight(new ParticleSystem(2000)) {
	/*
	Audio::bgmusic.play();
	Audio::bgmusic.setLoop(true);
	*/
	ball->followPlayer(*player);
	obstacles->setBlockColor(0, sf::Color::Black, sf::Color::Blue, sf::Color::Black, sf::Color::Black);
	obstacles->setBlockColor(1, sf::Color::Green, sf::Color::Black, sf::Color::Cyan, sf::Color::Black);
	obstacles->setBlockSpeed(0, 1.5f);
	obstacles->setBlockSpeed(1, -1.5f);	
	bricks->setBrickColor(sf::Color(static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(183), static_cast<sf::Uint8>(197)));
	addChild({ hud, obstacles, player, ball, bricks, mouseLight });
}

Stage::~Stage() {
	Audio::bgmusic.stop();
	Audio::sound1.stop();
}

void Stage::update(float updateSpan ,sf::Vector2i mousePosition) {
	if (!GameState::pause) {
		player->playerMove();
		ball->ballUpdateMove(*player, Audio::sound1);
		if (GameState::start) {
			obstacles->update(*ball);
			bricks->update(*ball);
			ball->move(*player);
			if (bricks->isEmpty()) {
				GameState::ready = false;
				GameState::start = false;
				GameState::reflash = true;
				std::cout << "Finished level: " << level++ << "!!!" << std::endl;
				bricks->reset(level);
				bricks->setBrickColor(sf::Color(static_cast<sf::Uint8>(rng() % 255), static_cast<sf::Uint8>(rng() % 255), static_cast<sf::Uint8>(rng() % 255)));
			}
		}
		else {
			ball->followPlayer(*player);
			if (!GameState::ready) {
				obstacles->update();
				GameState::ready = true;
			}
		}
	}

	mouseLight->setEmitPosition(window.mapPixelToCoords(mousePosition));
	mouseLight->update(updateSpan);
}
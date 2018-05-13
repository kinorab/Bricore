#include "stage.h"
#include "define.h"
#include "audio.h"
#include "hud.h"
#include "particleSystem.h"
#include "obstacle.h"
#include "ball.h"
#include "player.h"
#include "brick.h"

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
// use getInstance() prevent return nullptr
std::shared_ptr<Stage> Stage::getPreInstance() {
	if (instance) {
		getInstance()->setPredict();
		getInstance()->predictUpdate();
	}
	return getInstance();
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
	try {
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
	}
	catch (std::exception &ex) {
		std::cout << "Exception in Stage::update(): " << ex.what() << std::endl;
	}
}

void Stage::updateMouseLight(float updateSpan, sf::Vector2f mousePosition) {
	mouseLight->setEmitPosition(mousePosition);
	mouseLight->update(updateSpan);
}

Stage::Stage()
	: HUDs(new HUD())
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
	addChild({ HUDs, player, ball, brick, obstacle, mouseLight });
}

void Stage::setPredict() {
	try {
		removeChild({ playerPredict, ballPredict, brickPredict, obstaclePredict });
		playerPredict.reset(new Player(*player));
		ballPredict.reset(new item::Ball(*ball));
		brickPredict.reset(new item::Brick(*brick));
		obstaclePredict.reset(new Obstacle(*obstacle));
		addChildAt({ playerPredict }, getChildIndex(player.get()) + 1);
		addChildAt({ ballPredict }, getChildIndex(ball.get()) + 1);
		addChildAt({ brickPredict }, getChildIndex(brick.get()) + 1);
		addChildAt({ obstaclePredict }, getChildIndex(obstacle.get()) + 1);
	}
	catch (std::out_of_range &ex) {
		std::cout << "Out_of_range in Stage::setPredict():" << ex.what() << std::endl;
	}
}

void Stage::predictUpdate() {
	try {
		if (!GameState::pause) {
			for (size_t i = 0; i < SLICE; ++i) {
				playerPredict->update(ballPredict->getMainBallPosition(), ballPredict->getMainBallRadius());
				if (GameState::start) {
					brickPredict->preUpdate(*ballPredict);
					obstaclePredict->preUpdate(*ballPredict);
					ballPredict->preUpdate(playerPredict->getMainPlayerDP());
				}
			}
		}
	}
	catch (std::exception &ex) {
		std::cout << "Exception in Stage::predictUpdate(): " << ex.what() << std::endl;
	}
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


#include "main.h"
#include "audio.h"
#include "ellipse.h"
#include "particleSystem.h"
#include "brick.h"
#include "define.h"
#include "hud.h"
#include "obstacle.h"
#include "UIFactory.h"
#include <iostream>
#include <map>
#include <stdexcept>
#include <queue>
#include <mutex>
#include <Windows.h>

using namespace sf;
using namespace std;
using namespace item;

static queue<Event> gameEventQueue;
static mutex gameEventQueueMutex;
static map<Keyboard::Key, bool> keyDown;

void renderThread(RenderWindow * window, atomic<bool> * done) {
	HIMC hIMC = 0x0;
	//hIMC = ImmAssociateContext(window->getSystemHandle(), hIMC);
	window->setActive(true);
	Audio::initialize();
	for (Keyboard::Key i = Keyboard::Unknown; i < Keyboard::Unknown + Keyboard::KeyCount; i = static_cast<Keyboard::Key>(i + 1)) {
		keyDown.insert({ i, false });
	}
	static float blockLength = 100.f;
	static float incre1 = 3.f;
	shared_ptr<Obstacle> obstacles(new Obstacle(2
		, { Vector2f(blockLength, blockLength * incre1), Vector2f(LEVEL_WIDTH - blockLength * 2, blockLength * incre1) }
	, { Vector2f(blockLength, blockLength * incre1), Vector2f(blockLength, blockLength * incre1) }));
	obstacles->setBlockColor(0, Color::Black, Color::Blue, Color::Black, Color::Black);
	obstacles->setBlockColor(1, Color::Green, Color::Black, Color::Cyan, Color::Black);
	obstacles->setBlockSpeed(0, 1.5f);
	obstacles->setBlockSpeed(1, -1.5f);
	shared_ptr<Player> player(new Player(5.5f));

	shared_ptr<Ball> ball(new Ball(*player));

	shared_ptr<Brick> bricks(new Brick(1, 60.f, 25.f, Vector2f(0.8f, 2.f), 3.f));
	bricks->setBrickColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(183), static_cast<Uint8>(197)));

	shared_ptr<HUD> hud(new HUD());

	shared_ptr<ParticleSystem> mouseLight(new ParticleSystem(2000));
	Vector2i localPosition;
	Mouse::setPosition(static_cast<Vector2i>(Vector2f(LEVEL_WIDTH / 2, LEVEL_HEIGHT / 2)), *window);

	DefaultContainer stage;
	stage.addChild({ obstacles, player, ball, bricks, hud, mouseLight });

	Time elapsed = milliseconds(0);
	Clock clock;
	bool finishing = false;

	while (!finishing) {

		Event currentEvent;
		Vector2i mousePosition = Mouse::getPosition(*window);

		while (!gameEventQueue.empty()) {

			gameEventQueueMutex.lock();
			currentEvent = gameEventQueue.front();
			gameEventQueue.pop();
			gameEventQueueMutex.unlock();

			handleKeyEvent(currentEvent);
			handleMouseEvent(currentEvent);

			if (currentEvent.type == Event::Closed) {
				Audio::bgmusic.stop();
				Audio::sound1.stop();
				finishing = true;
			}
		}

		// maximum update span
		elapsed += clock.restart();
		if (elapsed.asSeconds() > 0.05f) {
			elapsed = seconds(0.05f);
		}

		// updateSpan: milliseconds
		static constexpr float updateSpan = 13.0f;
		while (elapsed.asSeconds() * 1000.0f > updateSpan) {
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
						cout << "Finished level: " << level++ << "!!!" << endl;
						bricks->reset(level);
						bricks->setBrickColor(Color(static_cast<Uint8>(rng() % 255), static_cast<Uint8>(rng() % 255), static_cast<Uint8>(rng() % 255)));
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
			mouseLight->setEmitPosition(window->mapPixelToCoords(mousePosition));
			mouseLight->update(updateSpan);
			elapsed -= seconds(updateSpan / 1000.0f);
		}

		// render
		window->clear(Color::White);
		window->draw(stage);
		window->display();
	}
	// finalize...
	*done = true;
}

void handleKeyEvent(sf::Event & event) {
	if (event.type != Event::KeyPressed
		&& event.type != Event::KeyReleased) {
		return;
	}

	if (event.type == Event::KeyPressed) {
		if (keyDown[event.key.code]) return;
		keyDown[event.key.code] = true;
		if (keyDown[Keyboard::P]) {
			GameState::pause = !GameState::pause;
			GameState::lock = !GameState::lock;
		}
		if (GameState::lock) {
			return; 
		}
		else {
			if (keyDown[Keyboard::G]) {
				GameState::start = true;
			}
		}
	}
	else if (event.type == Event::KeyReleased) {
		if (!keyDown[event.key.code]) return;
		keyDown[event.key.code] = false;
	}
}

void handleMouseEvent(sf::Event & event) {
	if (event.type == Event::MouseButtonPressed) {
		if (!GameState::lock) {
			if (event.mouseButton.button == Mouse::Left) {
				GameState::start = true;
			}
			// debugging feature
			else if (event.mouseButton.button == Mouse::Right) {
				GameState::start = false;
				GameState::ready = false;
			}
		}
	}
	else if (event.type == Event::MouseEntered) {
		GameState::light = true;
	}
	else if (event.type == Event::MouseLeft) {
		GameState::light = false;
	}
}

int main() {
	ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 6;
	settings.majorVersion = 4;
	settings.minorVersion = 1;

	RenderWindow window(VideoMode(static_cast<int>(GAME_WIDTH), static_cast<int>(GAME_HEIGHT)), "Pigject", Style::Titlebar | Style::Close, settings);
	window.setMouseCursorVisible(false);
	window.setPosition(Vector2i(window.getPosition().x, 20));
	window.setVerticalSyncEnabled(true);
	window.setActive(false);
	atomic <bool> done(false);
	thread subthread(renderThread, &window, &done);
	// main thread wait for event and push to queue
	Event event;
	while (!done && window.waitEvent(event)) {

		gameEventQueueMutex.lock();
		gameEventQueue.push(event);
		gameEventQueueMutex.unlock();
	}

	// finalize...
	window.close();
	subthread.join();
	system("pause");
	return 0;
}

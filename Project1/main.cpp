#include "main.h"
#include "stage.h"
#include <iostream>
#include <map>
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
	/*
	HIMC hIMC = 0x0;
	hIMC = ImmAssociateContext(window->getSystemHandle(), hIMC);
	*/
	Audio::initialize();
	/*
	Audio::bgmusic.play();
	Audio::bgmusic.setLoop(true);
	*/
	for (Keyboard::Key i = Keyboard::Unknown;
		i < Keyboard::Unknown + Keyboard::KeyCount;
		i = static_cast<Keyboard::Key>(i + 1)) {
		keyDown.insert({ i, false });
	}
	
	Stage stage(*window);

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
				finishing = true;
			}
		}

		// maximum update span
		elapsed = min<Time>(elapsed + clock.restart(), seconds(0.05f));

		// updateSpan: milliseconds
		static constexpr float updateSpan = 13.0f;
		while (elapsed.asSeconds() * 1000.0f > updateSpan) {
			stage.update(updateSpan, mousePosition);
			elapsed -= seconds(updateSpan / 1000.0f);
		}

		// render
		window->clear(Color::White);
		window->draw(stage);
		window->display();
	}

	// finalize...
	Audio::bgmusic.stop();
	Audio::sound1.stop();
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

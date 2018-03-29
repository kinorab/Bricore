#include "game.h"
#include "audio.h"
#include "stage.h"
#include <Windows.h>

using namespace sf;
using namespace std;

atomic<bool> Game::finished(false);
queue<Event> Game::eventQueue;
mutex Game::eventQueueMutex;
map<Keyboard::Key, bool> Game::keyDown;
thread Game::renderThread;
Event Game::currentEvent;
Event Game::nextEvent;
ContextSettings Game::settings;
RenderWindow Game::window;

void Game::run() {
	settleWindow();
	renderThread = thread(renderFunc);
	while (!finished && window.waitEvent(nextEvent)) {
		pushEvent();
	}
	window.close();
}

void Game::pushEvent() {
	eventQueueMutex.lock();
	eventQueue.push(nextEvent);
	eventQueueMutex.unlock();
}

void Game::settleWindow() {
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 6;
	settings.majorVersion = 4;
	settings.minorVersion = 1;
	window.create(VideoMode(static_cast<size_t>(GAME_WIDTH), static_cast<size_t>(GAME_HEIGHT)), "BricksEx", Style::Close, settings);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	window.setPosition(Vector2i(window.getPosition().x, 20));
	ImmAssociateContext(window.getSystemHandle(), 0);
	window.setActive(false);
}

void Game::popEvent() {
	eventQueueMutex.lock();
	currentEvent = eventQueue.front();
	eventQueue.pop();
	eventQueueMutex.unlock();
}

void Game::handleKeyEvent(Event & event) {
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

void Game::handleMouseEvent(Event & event) {
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

void Game::renderFunc() {

	Audio::initialize();
	for (Keyboard::Key i = Keyboard::Unknown;
		i < Keyboard::Unknown + Keyboard::KeyCount;
		i = static_cast<Keyboard::Key>(i + 1)) {
		keyDown.insert({ i, false });
	}

	Stage stage(window);
	Time elapsed = milliseconds(0);
	Clock clock;
	bool finishing = false;

	while (!finishing) {

		while (!eventQueue.empty()) {
			popEvent();
			handleKeyEvent(currentEvent);
			handleMouseEvent(currentEvent);

			if (currentEvent.type == Event::Closed) {
				finishing = true;
			}
		}

		// maximum update span
		elapsed = min<Time>(elapsed + clock.restart(), seconds(0.05f));

		// updateSpan: milliseconds
		Vector2i mousePosition = Mouse::getPosition(window);
		static constexpr float updateSpan = 13.0f;
		while (elapsed.asSeconds() * 1000.0f > updateSpan) {
			stage.update(updateSpan, mousePosition);
			elapsed -= seconds(updateSpan / 1000.0f);
		}

		// render
		window.clear(Color::White);
		window.draw(stage);
		window.display();
	}

	// finalize...
	window.setActive(false);
	finished = true;
}

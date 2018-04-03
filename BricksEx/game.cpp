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
ContextSettings Game::settings;
RenderWindow Game::window;

void Game::run() {
	settleWindow();
	renderThread = thread(renderFunc);
	Event nextEvent;
	while (!finished && window.waitEvent(nextEvent)) {
		pushEvent(nextEvent);
	}
	window.close();
}

void Game::pushEvent(Event & event) {
	eventQueueMutex.lock();
	eventQueue.push(event);
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

Event Game::popEvent() {
	eventQueueMutex.lock();
	Event event = eventQueue.front();
	eventQueue.pop();
	eventQueueMutex.unlock();
	return event;
}

void Game::handleKeyEvent() {
	if (currentEvent.type != Event::KeyPressed
		&& currentEvent.type != Event::KeyReleased) {
		return;
	}

	if (currentEvent.type == Event::KeyPressed) {
		if (keyDown[currentEvent.key.code]) return;
		keyDown[currentEvent.key.code] = true;
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
	else if (currentEvent.type == Event::KeyReleased) {
		if (!keyDown[currentEvent.key.code]) return;
		keyDown[currentEvent.key.code] = false;
	}
}

void Game::handleMouseEvent() {
	if (currentEvent.type == Event::MouseButtonPressed) {
		if (!GameState::lock) {
			if (currentEvent.mouseButton.button == Mouse::Left) {
				GameState::start = true;
			}
			// debugging feature
			else if (currentEvent.mouseButton.button == Mouse::Right) {
				GameState::start = false;
				GameState::ready = false;
			}
		}
	}
	else if (currentEvent.type == Event::MouseEntered) {
		GameState::light = true;
	}
	else if (currentEvent.type == Event::MouseLeft) {
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

	shared_ptr<Stage> stage(new Stage());
	stage->initialize();
	Time elapsed = milliseconds(0);
	Clock clock;
	bool finishing = false;

	while (!finishing) {

		while (!eventQueue.empty()) {
			currentEvent = popEvent();
			handleKeyEvent();
			handleMouseEvent();

			if (currentEvent.type == Event::Closed) {
				finishing = true;
			}
		}

		// maximum update span
		elapsed = min<Time>(elapsed + clock.restart(), seconds(0.05f));

		// updateSpan: milliseconds
		Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
		static constexpr float updateSpan = 13.0f;
		while (elapsed.asSeconds() * 1000.0f > updateSpan) {
			stage->update(updateSpan, mousePosition);
			elapsed -= seconds(updateSpan / 1000.0f);
		}

		// render
		window.draw(*stage);
		window.display();
	}

	// finalize...
	window.setActive(false);
	finished = true;
}

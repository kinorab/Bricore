#include "game.h"
#include "audio.h"
#include "define.h"
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
shared_ptr<Stage> Game::stage;
Vector2f Game::mousePosition;
shared_ptr<game::InteractiveObject> Game::previousContactNode(nullptr);

void Game::run() {
	settleWindow();
	renderThread = thread(renderFunc);
	Event nextEvent;
	while (!finished && window.waitEvent(nextEvent)) {
		pushEvent(nextEvent);
	}
	window.close();
}

void Game::pushEvent(const Event & event) {
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
	}
	else if (currentEvent.type == Event::KeyReleased) {
		if (!keyDown[currentEvent.key.code]) return;
		keyDown[currentEvent.key.code] = false;
	}

	game::Event event(currentEvent.type, false, true);
	event.data = currentEvent.key;
	stage->dispatchEvent(&event);
}

void Game::handleMouseEvent() {
	if (currentEvent.type == Event::MouseMoved) {
		mousePosition = window.mapPixelToCoords((Vector2i(currentEvent.mouseMove.x, currentEvent.mouseMove.y)));
		std::shared_ptr<game::InteractiveObject> contactNode;
		if (mousePosition.x < 0 || mousePosition.x > GAME_WIDTH
			|| mousePosition.y < 0 || mousePosition.y > GAME_HEIGHT) {
			contactNode = nullptr;
		}
		else {
			contactNode = stage->getObjectUnderPoint(mousePosition);
			if (contactNode) {
				game::Event event(currentEvent.type, true, true);
				event.data = currentEvent.mouseMove;
				contactNode->dispatchEvent(&event);
			}
		}

		if (contactNode != previousContactNode) {
			vector<shared_ptr<game::InteractiveObject>> previousNodes;
			for (shared_ptr<game::InteractiveObject> node = previousContactNode; node; node = node->getParent().lock()) {
				previousNodes.push_back(node);
			}

			vector<shared_ptr<game::InteractiveObject>> currentNodes;
			for (shared_ptr<game::InteractiveObject> node = contactNode; node; node = node->getParent().lock()) {
				currentNodes.push_back(node);
			}

			int sameNodeCount = 0;
			if (previousContactNode && contactNode) {
				for (; *(previousNodes.rbegin() + sameNodeCount) == *(currentNodes.rbegin() + sameNodeCount); sameNodeCount += 1);
			}

			std::for_each(previousNodes.begin(), previousNodes.end() - sameNodeCount,
				[](shared_ptr<game::InteractiveObject> & node) {
				game::Event event(Event::MouseLeft, false, true);
				node->dispatchEvent(&event);
			});

			std::for_each(currentNodes.begin(), currentNodes.end() - sameNodeCount,
				[](shared_ptr<game::InteractiveObject> & node) {
				game::Event event(Event::MouseEntered, false, true);
				node->dispatchEvent(&event);
			});

			previousContactNode = contactNode;
		}
	}
	else if (currentEvent.type == Event::MouseButtonPressed) {
		if (previousContactNode) {
			game::Event event(currentEvent.type, true, true);
			event.data = currentEvent.mouseButton;
			previousContactNode->dispatchEvent(&event);
		}
	}
	else if (currentEvent.type == Event::MouseButtonReleased) {
		if (previousContactNode) {
			game::Event event(currentEvent.type, true, true);
			event.data = currentEvent.mouseButton;
			previousContactNode->dispatchEvent(&event);
		}
	}
	else if (currentEvent.type == Event::MouseLeft) {
		Event event;
		event.type = Event::MouseMoved;
		event.mouseMove = { -1, -1 };
		pushEvent(event);
	}
}

void Game::renderFunc() {
	Audio::initialize();
	for (Keyboard::Key i = Keyboard::Unknown;
		i < Keyboard::Unknown + Keyboard::KeyCount;
		i = static_cast<Keyboard::Key>(i + 1)) {
		keyDown.insert({ i, false });
	}

	stage.reset(new Stage());
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

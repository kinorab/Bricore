#include "game.h"
#include "audio.h"
#include "define.h"
#include "stage.h"
#include <iostream>
#include <Windows.h>

using namespace sf;
using namespace std;

atomic<bool> Game::finished(false);
queue<Event> Game::eventQueue;
mutex Game::eventQueueMutex;
map<Keyboard::Key, bool> Game::keyDown;
thread Game::renderThread;
Event Game::currentEvent;
Graphics Game::graph;
RenderWindow Game::window(VideoMode(static_cast<size_t>(GAME_WIDTH), static_cast<size_t>(GAME_HEIGHT))
	, "BricksEx", Style::Close, graph.getSettings());
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
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	window.setPosition(Vector2i(window.getPosition().x, 20));
	ImmAssociateContext(window.getSystemHandle(), 0);
	sf::Uint8 a[] = { 255, 255, 255, 255,	 0, 0, 0, 255 };
	window.setIcon(2, 1, a);
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
	Stage::getInstance()->dispatchEvent(&event);
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
			contactNode = Stage::getInstance()->getObjectUnderPoint(mousePosition);
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

void Game::handleFrameEvent() {
	//window.create(window.getSystemHandle(), settings);
}

void Game::renderFunc() {
	Audio::initialize();
	for (Keyboard::Key i = Keyboard::Unknown;
		i < Keyboard::Unknown + Keyboard::KeyCount;
		i = static_cast<Keyboard::Key>(i + 1)) {
		keyDown.insert({ i, false });
	}
	// display in milliseconds
	constexpr float updateSpan = 0.013f * 1000.f;
	Time elapsed = milliseconds(0);
	Time renderElapsed = milliseconds(0);
	Time distribute = milliseconds(0);
	Clock clock;
	bool finishing = false;

	while (!finishing) {
		distribute = clock.restart();
		elapsed += distribute;
		renderElapsed += distribute;
		while (!eventQueue.empty()) {
			currentEvent = popEvent();
			handleKeyEvent();
			handleMouseEvent();
			handleFrameEvent();
			if (currentEvent.type == Event::Closed) {
				finishing = true;
			}
		}
		// max fixed at 1.5x current fps
		renderElapsed = min<Time>(renderElapsed, milliseconds(static_cast<Int32>(graph.getFrameSpan() * 1.5f)));

		while (elapsed.asMicroseconds() >= updateSpan * 1000.f) {
			elapsed -= milliseconds(static_cast<Int32>(updateSpan));
			window.draw(*Stage::getPreInstance(elapsed.asMilliseconds() / updateSpan));
			Stage::getInstance()->update(updateSpan, mousePosition);
		}
		if (renderElapsed.asMicroseconds() >= graph.getFrameSpan() * 1000.f) {
			window.display();
			renderElapsed -= milliseconds(static_cast<Int32>(graph.getFrameSpan()));
		}
	}
	// finalize...
	window.setActive(false);
	finished = true;
}

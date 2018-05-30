#include "game.h"
#include "audioManager.h"
#include "define.h"
#include "stage.h"
#include <Windows.h>

using namespace sf;
using namespace std;

bool Game::instantiated;

Game::Game()
	: finished(false)
	, stage(new Stage()) {
	if (instantiated) {
		throw std::invalid_argument("This class can only be instantiated once!");
	}

	window.reset(new RenderWindow(VideoMode(static_cast<size_t>(GAME_WIDTH), static_cast<size_t>(GAME_HEIGHT))
		, "BricksEx", Style::Close, graph.getSettings()));
	instantiated = true;
}

Game::~Game() {
	instantiated = false;
}

void Game::run() {
	settleWindow();
	renderThread = thread(std::bind(&Game::renderFunc, this));
	Event nextEvent;
	while (!finished && window->waitEvent(nextEvent)) {
		pushEvent(nextEvent);
	}
	window->close();
}

void Game::pushEvent(const Event & event) {
	eventQueueMutex.lock();
	eventQueue.push(event);
	eventQueueMutex.unlock();
}

void Game::settleWindow() {
	window->setMouseCursorVisible(false);
	window->setVerticalSyncEnabled(true);
	window->setPosition(Vector2i(window->getPosition().x, 20));
	ImmAssociateContext(window->getSystemHandle(), 0);
	//window.setIcon(graph.getIconSize().x, graph.getIconSize().y, graph.getIcon());
	window->setActive(false);
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
		mousePosition = window->mapPixelToCoords((Vector2i(currentEvent.mouseMove.x, currentEvent.mouseMove.y)));
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
			for (shared_ptr<game::InteractiveObject> node = previousContactNode; node;) {
				previousNodes.push_back(node);
				game::Container * parent = node->getParent();
				if (parent) {
					node = parent->shared_from_this();
				}
				else {
					node = nullptr;
				}
			}

			vector<shared_ptr<game::InteractiveObject>> currentNodes;
			for (shared_ptr<game::InteractiveObject> node = contactNode; node;) {
				currentNodes.push_back(node);
				game::Container * parent = node->getParent();
				if (parent) {
					node = parent->shared_from_this();
				}
				else {
					node = nullptr;
				}
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

void Game::handleGraphicsEvent() {
	//window.create(window.getSystemHandle(), settings);
}

void Game::renderFunc() {
	AudioManager::getInstance()->initialize();
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
		distribute = min<Time>(clock.restart(), milliseconds(500));
		elapsed += distribute;
		renderElapsed += distribute;
		while (!eventQueue.empty()) {
			currentEvent = popEvent();
			handleKeyEvent();
			handleMouseEvent();
			handleGraphicsEvent();
			if (currentEvent.type == Event::Closed) {
				finishing = true;
			}
		}
		// max fixed at 1.5x current fps
		renderElapsed = min<Time>(renderElapsed, milliseconds(static_cast<Int32>(graph.getFrameSpan() * 1.5f)));

		while (elapsed.asMicroseconds() >= updateSpan * 1000.f) {
			stage->update(updateSpan, mousePosition);
			elapsed -= milliseconds(static_cast<Int32>(updateSpan));
		}

		if (renderElapsed.asMicroseconds() >= graph.getFrameSpan() * 1000.f) {
			stage->predictUpdate(elapsed.asMilliseconds() / updateSpan);
			window->draw(*stage);
			window->display();
			renderElapsed -= milliseconds(static_cast<Int32>(graph.getFrameSpan()));
		}
	}
	// finalize...
	window->setActive(false);
	finished = true;
}

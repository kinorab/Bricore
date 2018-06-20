#include "game.h"
#include "event/event.h"
#include "manager/audioManager.h"
#include "definition/define.h"
#include "stage.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>

using namespace sf;

Game::Game() :
	finished(false),
	stage(new Stage()) {
	window.reset(new RenderWindow(VideoMode(static_cast<size_t>(GAME_WIDTH), static_cast<size_t>(GAME_HEIGHT))
		, "BricksEx", Style::Close, graph.getSettings()));
}

Game::~Game() {
}

void Game::run() {
	settleWindow();
	renderThread = std::thread(std::bind(&Game::renderFunc, this));
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

	game::EventType eventType;
	if (currentEvent.type == Event::KeyPressed) {
		if (keyDown[currentEvent.key.code]) return;
		keyDown[currentEvent.key.code] = true;
		eventType = game::EventType::KeyPressed;
	}
	else if (currentEvent.type == Event::KeyReleased) {
		if (!keyDown[currentEvent.key.code]) return;
		keyDown[currentEvent.key.code] = false;
		eventType = game::EventType::KeyReleased;
	}

	game::Event event(eventType, false, true);
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
				game::Event event(game::EventType::MouseMoved, true, true);
				event.data = currentEvent.mouseMove;
				contactNode->dispatchEvent(&event);
			}
		}

		if (contactNode != previousContactNode) {
			std::vector<std::shared_ptr<game::InteractiveObject>> previousNodes;
			for (std::shared_ptr<game::InteractiveObject> node = previousContactNode; node;) {
				previousNodes.push_back(node);
				game::Container * parent = node->getParent();
				if (parent) {
					node = parent->shared_from_this();
				}
				else {
					node = nullptr;
				}
			}

			std::vector<std::shared_ptr<game::InteractiveObject>> currentNodes;
			for (std::shared_ptr<game::InteractiveObject> node = contactNode; node;) {
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
				while (*(previousNodes.rbegin() + sameNodeCount) == *(currentNodes.rbegin() + sameNodeCount)) {
					sameNodeCount += 1;
				}
			}

			std::for_each(previousNodes.begin(), previousNodes.end() - sameNodeCount,
				[](std::shared_ptr<game::InteractiveObject> & node) {
				game::Event event(game::EventType::MouseLeft, false, true);
				node->dispatchEvent(&event);
			});

			std::for_each(currentNodes.begin(), currentNodes.end() - sameNodeCount,
				[](std::shared_ptr<game::InteractiveObject> & node) {
				game::Event event(game::EventType::MouseEntered, false, true);
				node->dispatchEvent(&event);
			});

			previousContactNode = contactNode;
		}
	}
	else if (currentEvent.type == Event::MouseButtonPressed && previousContactNode) {
		game::Event event(game::EventType::MouseButtonPressed, true, true);
		event.data = currentEvent.mouseButton;
		previousContactNode->dispatchEvent(&event);
	}
	else if (currentEvent.type == Event::MouseButtonReleased && previousContactNode) {
		game::Event event(game::EventType::MouseButtonReleased, true, true);
		event.data = currentEvent.mouseButton;
		previousContactNode->dispatchEvent(&event);
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
	AudioManager::getInstance().initialize();
	for (Keyboard::Key i = Keyboard::Unknown;
		i < Keyboard::Unknown + Keyboard::KeyCount;
		i = static_cast<Keyboard::Key>(i + 1)) {
		keyDown.insert({ i, false });
	}

	float elapsed = 0.f;
	float renderElapsed = 0.f;
	Clock clock;
	Clock clock2;
	bool finishing = false;

	while (!finishing) {
		// display in milliseconds
		constexpr float updateSpan = 13.f;
		float distribute = clock.restart().asSeconds() * 1000.f;
		while (!eventQueue.empty()) {
			currentEvent = popEvent();
			handleKeyEvent();
			handleMouseEvent();
			handleGraphicsEvent();
			if (currentEvent.type == Event::Closed) {
				finishing = true;
			}
		}
		elapsed = std::min<float>(elapsed + distribute, updateSpan * 1.5f);
		while (elapsed > 0.0f) {
			float intervalRate = std::min<float>(elapsed, updateSpan) / updateSpan;
			stage->update(updateSpan, intervalRate);
			elapsed -= updateSpan * intervalRate;
		}
		// max fixed at 1.5x current fps
		renderElapsed = std::min<float>(renderElapsed + distribute, graph.getFrameSpan() * 1.5f);
		if (renderElapsed >= graph.getFrameSpan()) {
			window->draw(*stage);
			window->display();
			renderElapsed -= graph.getFrameSpan();
		}
	}
	// finalize...
	window->setActive(false);
	finished = true;
}

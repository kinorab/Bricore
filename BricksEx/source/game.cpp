#include "game.h"
#include "event/keyEvent.h"
#include "event/mouseButtonEvent.h"
#include "event/mouseMoveEvent.h"
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
		eventQueue.push(nextEvent);
	}
	window->close();
}

void Game::settleWindow() {
	window->setMouseCursorVisible(false);
	window->setVerticalSyncEnabled(true);
	window->setPosition(Vector2i(window->getPosition().x, 20));
	ImmAssociateContext(window->getSystemHandle(), 0);
	//window.setIcon(graph.getIconSize().x, graph.getIconSize().y, graph.getIcon());
	window->setActive(false);
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

	game::KeyEvent event(eventType, currentEvent.key);
	stage->dispatchEvent(event);
}

void Game::handleMouseEvent() {
	if (currentEvent.type == Event::MouseMoved) {
		sf::Vector2i mousePosition = { currentEvent.mouseMove.x, currentEvent.mouseMove.y };
		std::cout << currentEvent.mouseMove.x << ", " << currentEvent.mouseMove.y << std::endl;
		std::shared_ptr<game::InteractiveObject> contactNode;
		if (mousePosition.x < 0 || mousePosition.x > GAME_WIDTH
			|| mousePosition.y < 0 || mousePosition.y > GAME_HEIGHT) {
			contactNode = nullptr;
		}
		else {
			contactNode = stage->getObjectUnderPoint(sf::Vector2f(mousePosition));
			if (contactNode) {
				game::MouseMoveEvent event(game::EventType::MouseMoved, currentEvent.mouseMove);
				contactNode->dispatchEvent(event);
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
				[&](std::shared_ptr<game::InteractiveObject> & node) {
				game::MouseMoveEvent event(game::EventType::MouseLeft, { mousePosition.x, mousePosition.y});
				node->dispatchEvent(event);
			});

			std::for_each(currentNodes.begin(), currentNodes.end() - sameNodeCount,
				[&](std::shared_ptr<game::InteractiveObject> & node) {
				game::MouseMoveEvent event(game::EventType::MouseEntered, { mousePosition.x, mousePosition.y });
				node->dispatchEvent(event);
			});

			previousContactNode = contactNode;
		}
	}
	else if (currentEvent.type == Event::MouseButtonPressed && previousContactNode) {
		game::MouseButtonEvent event(game::EventType::MouseButtonPressed, currentEvent.mouseButton);
		previousContactNode->dispatchEvent(event);
	}
	else if (currentEvent.type == Event::MouseButtonReleased && previousContactNode) {
		game::MouseButtonEvent event(game::EventType::MouseButtonReleased, currentEvent.mouseButton);
		previousContactNode->dispatchEvent(event);
	}
	else if (currentEvent.type == Event::MouseLeft) {
		Event event;
		event.type = Event::MouseMoved;
		event.mouseMove = { -1, -1 };
		std::cout << "left\n";
		eventQueue.push(event);
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
	// display in milliseconds
	constexpr float updateSpan = 0.013f * 1000.f;
	Time elapsed = milliseconds(0);
	Time renderElapsed = milliseconds(0);
	Time distribute = milliseconds(0);
	Clock clock;
	bool finishing = false;

	while (!finishing) {
		distribute = std::min<Time>(clock.restart(), milliseconds(500));
		elapsed += distribute;
		renderElapsed += distribute;
		while (!eventQueue.empty()) {
			currentEvent = eventQueue.pop();
			handleKeyEvent();
			handleMouseEvent();
			handleGraphicsEvent();
			if (currentEvent.type == Event::Closed) {
				finishing = true;
			}
		}
		// max fixed at 1.5x current fps
		renderElapsed = std::min<Time>(renderElapsed, milliseconds(static_cast<Int32>(graph.getFrameSpan() * 1.5f)));

		while (elapsed.asMicroseconds() >= updateSpan * 1000.f) {
			stage->update(updateSpan);
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

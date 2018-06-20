#include "game.h"
#include "manager/audioManager.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "stage.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <future>

Game::Game() :
	stage(new Stage()),
	mouseHandler({ static_cast<int>(GAME_WIDTH), static_cast<int>(GAME_HEIGHT) }) {
	window.reset(new sf::RenderWindow(sf::VideoMode(static_cast<size_t>(GAME_WIDTH), static_cast<size_t>(GAME_HEIGHT)),
		"BricksEx", sf::Style::Close, graph.getSettings()));
}

Game::~Game() = default;

void Game::run() {
	settleWindow();
	AudioManager::getInstance().initialize();
	std::future<void> renderThread = std::async(std::launch::async, &Game::renderFunc, this);
	sf::Event nextEvent;
	while (renderThread.wait_for(std::chrono::seconds(0)) != std::future_status::ready && window->waitEvent(nextEvent)) {
		eventQueue.push(nextEvent);
	}
	window->close();
}

void Game::settleWindow() {
	window->setMouseCursorVisible(false);
	window->setVerticalSyncEnabled(true);
	window->setPosition(sf::Vector2i(window->getPosition().x, 20));
	ImmAssociateContext(window->getSystemHandle(), 0);
	//window.setIcon(graph.getIconSize().x, graph.getIconSize().y, graph.getIcon());
	window->setActive(false);
}

void Game::renderFunc() {
	float elapsed = 0;
	float renderElapsed = 0;
	sf::Clock clock;

	for (bool finishing = false; !finishing;) {
		constexpr float updateSpan = 0.013f * 1000.f;
		const float distribute = clock.restart().asSeconds() * 1000;
		// maximum elapsed cap
		handleEvents(finishing);

		elapsed = std::min<float>(elapsed + distribute, 500);
		for (; elapsed >= updateSpan; elapsed -= updateSpan) {
			stage->update(updateSpan);
		}

		renderElapsed = std::min<float>(renderElapsed + distribute, graph.getFrameSpan() * 1.5f);
		if (renderElapsed >= graph.getFrameSpan()) {
			stage->predictUpdate(elapsed / updateSpan);
			window->draw(*stage);
			window->display();
			renderElapsed -= graph.getFrameSpan();
		}
	}
	// finalize...
	window->setActive(false);
}

void Game::handleEvents(bool & finishing) {
	while (!eventQueue.empty()) {
		sf::Event currentEvent = eventQueue.pop();
		mouseHandler.handle(currentEvent, *stage);
		keyboardHandler.handle(currentEvent, *stage);
		if (currentEvent.type == sf::Event::Closed) {
			finishing = true;
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

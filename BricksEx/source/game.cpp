#include "game.h"
#include "manager/audioManager.h"
#include "definition/gameState.h"
#include "definition/utility.h"
#include "stage.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <future>

using namespace sf;

Game::Game() :
	stage(new Stage()),
	mouseHandler({ static_cast<int>(GAME_WIDTH), static_cast<int>(GAME_HEIGHT) }) {
	window.reset(new RenderWindow(VideoMode(static_cast<size_t>(GAME_WIDTH), static_cast<size_t>(GAME_HEIGHT)),
		"BricksEx", Style::Close, graph.getSettings()));
}

Game::~Game() = default;

void Game::run() {
	settleWindow();
	Event nextEvent;

	std::future<void> renderThread = std::async(std::launch::async, &Game::renderFunc, this);
	while (renderThread.wait_for(std::chrono::seconds(0)) != std::future_status::ready && window->waitEvent(nextEvent)) {
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

void Game::renderFunc() {
	AudioManager::getInstance().initialize();
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
		// maximum elapsed cap
		renderElapsed = std::min<Time>(renderElapsed, milliseconds(static_cast<Int32>(graph.getFrameSpan() * 1.5f)));
		handleEvents(finishing);
		while (elapsed.asMilliseconds() >= updateSpan) {
			stage->update(updateSpan);
			elapsed -= milliseconds(static_cast<Int32>(updateSpan));
		}

		if (renderElapsed.asMilliseconds() >= graph.getFrameSpan()) {
			stage->predictUpdate(elapsed.asMilliseconds() / updateSpan);
			window->draw(*stage);
			window->display();
			renderElapsed -= milliseconds(static_cast<Int32>(graph.getFrameSpan()));
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
		if (currentEvent.type == Event::Closed) {
			finishing = true;
		}
	}
}

#include "game.h"
#include "stage.h"
#include "root.h"
#include "graphics.h"
#include "interact/container.h"
#include "manager/audioManager.h"
#include "handler/windowHandler.h"
#include "definition/utility.h"
#include "definition/gameState.h"
#include "definition/userSystem.h"
#include "gameSys/level/level.h"
#include "gameSys/data/data.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <future>

using namespace game;

Game::Game() noexcept
	: graph(new Graphics)
	, level(new Level)
	, data(new Data)
	, windowHandler(new WindowHandler)
	, bEnterToGame(false)
	, bExitGame(false) {
	window.reset(new sf::RenderWindow(sf::VideoMode(static_cast<size_t>(GAME_WIDTH), static_cast<size_t>(GAME_HEIGHT)),
		"Bricore", sf::Style::Close, graph->getSettings()));
	root.reset(new Root(graph, window));
	//if (saveData.exist() && root.chooseSave(saveData)) {
	//}
	//else { 
	level->changeSetting(Mode::_2Player, Diffculty::Hard);
	//}
	stage.reset(new Stage(level, root, window));
	level->bDefaultControlKeySettled = true;
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
	// subtract 9 because window setPosition() has no-reasonly plus default
	window->setPosition({ static_cast<int>(sys::getMonitorResolution().x - GAME_WIDTH) / 2 - 9, 20 });
	//window->setMouseCursor(graph->getCursor());
	//window->setIcon(graph->getIconSize().x, graph->getIconSize().y, graph->getIcon());
	ImmAssociateContext(window->getSystemHandle(), 0);
	window->setActive(false);
}

void Game::renderFunc() {
	float elapsed = 0;
	float renderElapsed = 0;
	sf::Clock clock;
	bEnterToGame = true;
	while (!bExitGame) {
		// display in milliseconds
		constexpr float updateSpan = 10.f;
		const float distribute = clock.restart().asSeconds() * 1000.f;
		auto handleFunc = std::async(std::launch::async, &Game::handleEvents, this);
		// maximum elapsed cap
		elapsed = std::min<float>(elapsed + distribute, updateSpan * 1.5f);
		while (elapsed > 0.0f) {
			float updateRatio = std::min<float>(elapsed, updateSpan) / updateSpan;
			auto rootFunc = std::async(std::launch::async, &Root::update, root, updateRatio);
			auto stageFunc = std::async(std::launch::async, &Stage::update, stage, updateRatio);
			elapsed -= updateSpan * updateRatio;
		}
		// maximum render elapsed cap
		renderElapsed = std::min<float>(renderElapsed + distribute, graph->getFrameSpan() * 1.5f);
		if (renderElapsed >= graph->getFrameSpan()) {
			window->draw(*stage);
			window->display();
			renderElapsed -= graph->getFrameSpan();
		}
	}
	// finalize...
	window->setActive(false);
}

void Game::handleEvents() {
	while (!eventQueue.empty()) {
		sf::Event currentEvent = eventQueue.pop();
		auto rootFunc = std::async(std::launch::async, &Root::handle, root, currentEvent);
		windowHandler->handle(currentEvent, *root);
		if (bEnterToGame) {
			auto stageFunc = std::async(std::launch::async, &Stage::handle, stage, currentEvent);
			windowHandler->handle(currentEvent, *stage);
		}
		if (currentEvent.type == sf::Event::Closed) {
			bExitGame = true;
		}
	}
}
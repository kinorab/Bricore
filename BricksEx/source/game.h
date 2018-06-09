#pragma once

#include "UI/graphics.h"
#include "interact/interactiveObject.h"
#include "SFMLEventQueue.h"
#include "SFMLMouseHandler.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Export.hpp>
#include <map>
#include <atomic>
#include <thread>

class Stage;

namespace sf {
	class RenderWindow;
}

class Game {
public:
	Game();
	virtual ~Game();
	virtual void run();

private:
	virtual void settleWindow();
	virtual void handleKeyEvent();
	virtual void handleGraphicsEvent();
	virtual void renderFunc();

	game::SFMLEventQueue eventQueue;
	game::SFMLMouseHandler mouseHandler;
	std::atomic<bool> finished;
	std::map<sf::Keyboard::Key, bool> keyDown;
	std::thread renderThread;
	sf::Event currentEvent;
	std::unique_ptr<sf::RenderWindow> window;
	std::shared_ptr<Stage> stage;
	Graphics graph;
};
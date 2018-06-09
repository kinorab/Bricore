#pragma once

#include "UI/graphics.h"
#include "interact/interactiveObject.h"
#include "SFMLEventQueue.h"
#include "SFMLMouseHandler.h"
#include "SFMLKeyboardHandler.h"
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
	virtual void renderFunc();

	game::SFMLEventQueue eventQueue;
	game::SFMLMouseHandler mouseHandler;
	game::SFMLKeyboardHandler keyboardHandler;
	std::atomic<bool> finished;
	std::thread renderThread;
	std::unique_ptr<sf::RenderWindow> window;
	std::shared_ptr<Stage> stage;
	Graphics graph;
};
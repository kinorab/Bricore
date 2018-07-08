#pragma once
#include "interact/interactiveObject.h"
#include "event/SFMLEventQueue.h"
#include "event/SFMLMouseHandler.h"
#include "event/SFMLKeyboardHandler.h"
#include <SFML/Window/Export.hpp>
#include <map>
#include <atomic>

namespace sf {
	class RenderWindow;
}

namespace game {
	class Root;
	class Stage;
	class Level;
}

class Graphics;

class Game {
public:
	Game();
	virtual ~Game();
	void run();

private:
	void settleWindow();
	void renderFunc();
	void handleEvents(bool & finishing);
	game::SFMLEventQueue eventQueue;
	game::SFMLMouseHandler mouseHandler;
	game::SFMLKeyboardHandler keyboardHandler;
	std::unique_ptr<sf::RenderWindow> window;
	std::shared_ptr<game::Stage> stage;
	std::shared_ptr<game::Root> root;
	std::shared_ptr<game::Level> level;
	std::shared_ptr<Graphics> graph;
};
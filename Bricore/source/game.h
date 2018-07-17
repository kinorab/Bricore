#pragma once
#include "event/eventQueue.h"
#include <SFML/Window/Export.hpp>
#include <map>

namespace sf {
	class RenderWindow;
}

namespace game {
	class Root;
	class Stage;
	class Level;
	class Data;
	class WindowHandler;
}

class Graphics;

class Game {
public:
	Game() noexcept;
	virtual ~Game();
	void run();

private:
	bool bEnterToGame;
	void settleWindow();
	void renderFunc();
	void handleEvents(bool & finishing);
	game::EventQueue eventQueue;
	game::WindowHandler * windowHandler;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Graphics> graph;
	std::shared_ptr<game::Stage> stage;
	std::shared_ptr<game::Root> root;
	std::shared_ptr<game::Level> level;
	std::shared_ptr<game::Data> data;
};
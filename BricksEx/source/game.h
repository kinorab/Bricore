#pragma once

#include "UI/graphics.h"
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
}

class Game {
public:
	Game();
	virtual ~Game();
	virtual void run();

private:
	virtual void settleWindow();
	virtual void renderFunc();
	virtual void handleEvents(bool & finishing);
	game::SFMLEventQueue eventQueue;
	game::SFMLMouseHandler mouseHandler;
	game::SFMLKeyboardHandler keyboardHandler;
	std::unique_ptr<sf::RenderWindow> window;
	std::shared_ptr<game::Root> stage;
	Graphics graph;
};
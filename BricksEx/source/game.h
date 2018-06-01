#pragma once

#include "UI/graphics.h"
#include "interact/interactiveObject.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Export.hpp>
#include <atomic>
#include <queue>
#include <map>
#include <mutex>

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
	static bool instantiated;
	virtual bool getInstantiated() const;
	virtual void setInstantiated(bool value);
	virtual void pushEvent(const sf::Event &);
	virtual void settleWindow();
	virtual sf::Event popEvent();
	virtual void handleKeyEvent();
	virtual void handleMouseEvent();
	virtual void handleGraphicsEvent();
	virtual void renderFunc();

	std::atomic<bool> finished;
	std::queue<sf::Event> eventQueue;
	std::mutex eventQueueMutex;
	std::map<sf::Keyboard::Key, bool> keyDown;
	std::thread renderThread;
	sf::Event currentEvent;
	std::unique_ptr<sf::RenderWindow> window;
	sf::Vector2f mousePosition;
	std::shared_ptr<game::InteractiveObject> previousContactNode;
	std::shared_ptr<Stage> stage;
	Graphics graph;
};
#pragma once

#include "stage.h"
#include <atomic>
#include <queue>
#include <map>
#include <mutex>
#include <SFML/Graphics.hpp>

class Game {
public:
	static void run();
private:
	static std::atomic<bool> finished;
	static std::queue<sf::Event> eventQueue;
	static std::mutex eventQueueMutex;
	static std::map<sf::Keyboard::Key, bool> keyDown;
	static std::thread renderThread;
	static sf::Event currentEvent;
	static sf::ContextSettings settings;
	static sf::RenderWindow window;
	static std::shared_ptr<Stage> stage;
	static sf::Vector2f mousePosition;
	static std::shared_ptr<game::InteractiveObject> previousContactNode;
	static void pushEvent(const sf::Event & event);
	static void settleWindow();
	static sf::Event popEvent();
	static void handleKeyEvent();
	static void handleMouseEvent();
	static void renderFunc();
};
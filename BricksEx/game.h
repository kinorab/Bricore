#pragma once

#include <atomic>
#include <queue>
#include <map>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "interactiveObject.h"
#include "graphics.h"

class Game {
public:
	static void run();

private:
	static void pushEvent(const sf::Event &);
	static void settleWindow();
	static sf::Event popEvent();
	static void handleKeyEvent();
	static void handleMouseEvent();
	static void handleFrameEvent();
	static void renderFunc();

	static std::atomic<bool> finished;
	static std::queue<sf::Event> eventQueue;
	static std::mutex eventQueueMutex;
	static std::map<sf::Keyboard::Key, bool> keyDown;
	static std::thread renderThread;
	static sf::Event currentEvent;
	static sf::RenderWindow window;
	static sf::Vector2f mousePosition;
	static std::shared_ptr<game::InteractiveObject> previousContactNode;
	static Graphics graph;
};
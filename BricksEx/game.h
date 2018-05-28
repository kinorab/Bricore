#pragma once

#include "graphics.h"
#include "interactiveObject.h"
#include <SFML/Graphics.hpp>
#include <atomic>
#include <queue>
#include <map>
#include <mutex>

class Game {
public:
	static void run();

private:
	static void pushEvent(const sf::Event &);
	static void settleWindow();
	static sf::Event popEvent();
	static void handleKeyEvent();
	static void handleMouseEvent();
	static void handleGraphicsEvent();
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
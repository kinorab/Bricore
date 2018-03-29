#pragma once

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
	static void pushEvent();
	static std::queue<sf::Event> eventQueue;
	static std::mutex eventQueueMutex;
	static std::map<sf::Keyboard::Key, bool> keyDown;
	static std::thread renderThread;
	static sf::Event nextEvent;
	static sf::Event currentEvent;
	static void settleWindow();
	static void popEvent();
	static void handleKeyEvent(sf::Event & event);
	static void handleMouseEvent(sf::Event & event);
	static void renderFunc();
	static sf::ContextSettings settings;
	static sf::RenderWindow window;
};
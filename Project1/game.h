#pragma once

#include <atomic>
#include <queue>
#include <map>
#include <mutex>
#include <SFML/Graphics.hpp>

class Game {
public:
	static std::atomic<bool> finished;
	static void pushEvent(sf::Event event);
	static void start(sf::RenderWindow & window);
private:
	static std::queue<sf::Event> eventQueue;
	static std::mutex eventQueueMutex;
	static std::map<sf::Keyboard::Key, bool> keyDown;
	static std::thread renderThread;
	static sf::Event popEvent();
	static void handleKeyEvent(sf::Event & event);
	static void handleMouseEvent(sf::Event & event);
	static void renderFunc(sf::RenderWindow * window);
};
#pragma once
#include <SFML/Window/Event.hpp>
#include <queue>
#include <mutex>

namespace game {
	class EventQueue {
	public:
		EventQueue() = default;
		virtual ~EventQueue() = default;
		virtual bool empty();
		virtual void push(const sf::Event & event);
		virtual sf::Event pop();
	private:
		std::queue<sf::Event> queue;
		std::mutex mutex;
	};
}
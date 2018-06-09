#include "SFMLEventQueue.h"
#include "definition/utility.h"

namespace game {
	bool SFMLEventQueue::empty() {
		mutex.lock();
		bool empty = queue.empty();
		mutex.unlock();
		return empty;
	}

	void SFMLEventQueue::push(const sf::Event & event) {
		mutex.lock();
		queue.push(event);
		mutex.unlock();
	}

	sf::Event SFMLEventQueue::pop() {
		mutex.lock();
		sf::Event event = queue.front();
		queue.pop();
		mutex.unlock();
		return event;
	}
}
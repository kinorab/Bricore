#include "defaultEvent.h"

game::DefaultEvent::DefaultEvent(std::string type, bool bubbles, bool cancelable) :
	bubbles(bubbles),
	cancelable(cancelable),
	defaultPrevented(false),
	eventPhase(game::EventPhase::NONE),
	propagationStopped(false),
	type(type) {

}

game::DefaultEvent::~DefaultEvent() {
	
}

bool game::DefaultEvent::getBubbles() const {
	return bubbles;
}

bool game::DefaultEvent::getCancelable() const {
	return cancelable;
}

game::EventDispatcher * game::DefaultEvent::getCurrentTarget() const {
	return nullptr;
}

bool game::DefaultEvent::getDefaultPrevented() const {
	return defaultPrevented;
}

game::EventPhase game::DefaultEvent::getEventPhase() const {
	return eventPhase;
}

game::EventDispatcher * game::DefaultEvent::getTarget() const {
	return nullptr;
}

std::string game::DefaultEvent::getType() const {
	return type;
}

void game::DefaultEvent::stopPropagation() {
	propagationStopped = true;
}

void game::DefaultEvent::preventDefault() {
	if (cancelable) {
		defaultPrevented = true;
	}
}

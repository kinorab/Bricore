#include "defaultEvent.h"

game::DefaultEvent::DefaultEvent(bool bubbles, bool cancelable) :
	bubbles(bubbles),
	cancelable(cancelable),
	defaultPrevented(false),
	eventPhase(game::EventPhase::NONE) {

}

game::DefaultEvent::~DefaultEvent() {

}

bool game::DefaultEvent::getBubbles() const
{
	return false;
}

bool game::DefaultEvent::getCancelable() const
{
	return false;
}

game::EventDispatcher * game::DefaultEvent::getCurrentTarget() const
{
	return nullptr;
}

bool game::DefaultEvent::getDefaultPrevented() const {
	return defaultPrevented;
}

game::EventPhase game::DefaultEvent::getEventPhase() const
{
	return EventPhase();
}

game::EventDispatcher * game::DefaultEvent::getTarget() const
{
	return nullptr;
}

std::string game::DefaultEvent::getType() const
{
	return std::string();
}

void game::DefaultEvent::stopPropagation()
{
}

void game::DefaultEvent::preventDefault()
{
}

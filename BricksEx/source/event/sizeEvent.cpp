#include "sizeEvent.h"
#include "sizeListener.h"

namespace game {
	SizeEvent::SizeEvent(EventType type, sf::Event::SizeEvent eventData) :
		Event(type, false, false),
		sf::Event::SizeEvent(eventData) {
	}

	void SizeEvent::accept(EventListener * visitor) {
		SizeListener * listener = dynamic_cast<SizeListener *>(visitor);
		if (listener) {
			listener->visit(this);
		}
		else {
			visitFailedHandler();
		}
	}
}

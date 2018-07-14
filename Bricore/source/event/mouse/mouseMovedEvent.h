#pragma once
#include "../UIEvent.h"
#include "../cancelable.h"
#include <SFML/Window/Event.hpp>

namespace sf {
	class RenderWindow;
}

namespace game {
	class MouseMovedEvent :
		public UIEvent,
		public Cancelable {
	public:
		// use mouse relate to window position
		explicit MouseMovedEvent(const std::shared_ptr<const sf::RenderWindow> & window);
		virtual ~MouseMovedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Vector2i moved;
	};
}
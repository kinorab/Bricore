#pragma once
#include "../UIEvent.h"
#include "../cancelable.h"
#include <SFML/Window/Event.hpp>

namespace sf {
	class RenderWindow;
}

namespace game {
	class MouseInSightEvent :
		public UIEvent,
		public Cancelable {
	public:
		// use mouse relate to window position
		explicit MouseInSightEvent(const std::shared_ptr<const sf::RenderWindow> & window);
		virtual ~MouseInSightEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Vector2i inSight;
	};
}
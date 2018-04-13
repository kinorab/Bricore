#pragma once

#include "event.h"
#include <functional>
#include <SFML/Graphics.hpp>

namespace game {
	class Container;

	class DisplayNode {
	public:
		virtual ~DisplayNode();
		virtual void addEventListener(std::string type, std::function<void(Event *)> callback);
		virtual void addEventListener(std::string type, std::function<void(Event *)> callback, bool useCapture);
		virtual bool containsPoint(const sf::Vector2f & point) const = 0;
		virtual bool dispatchEvent(Event * event);
		virtual std::shared_ptr<sf::Drawable> getDrawable() = 0;
		virtual std::weak_ptr<Container> getParent() const;
		virtual void initialize();
		virtual void removeEventListener(std::string type, std::function<void(Event *)> callback, bool useCapture);
		virtual void setParent(std::weak_ptr<Container> parent);
	private:
		struct EventListener {
			std::string type;
			std::function<void(Event *)> callback;
			bool useCapture;
		};

		std::vector<EventListener> listeners;
		std::weak_ptr<Container> parent;
	};
}
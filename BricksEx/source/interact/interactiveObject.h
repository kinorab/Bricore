#pragma once

#include "../event/eventType.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <functional>
#include <map>

namespace sf {
	class RenderTarget;
	class RenderStates;
}

namespace game {
	class Container;
	class Event;

	class InteractiveObject
		: public sf::Drawable,
		public sf::Transformable {
	public:
		InteractiveObject();
		virtual ~InteractiveObject();
		virtual int addEventListener(EventType type, std::function<void(Event *)> callback);
		virtual int addEventListener(EventType type, std::function<void(Event *)> callback, bool useCapture);
		virtual bool containsPoint(const sf::Vector2f & point) const = 0;
		virtual bool dispatchEvent(Event * event);
		virtual std::shared_ptr<sf::Drawable> getDrawable() const = 0;
		virtual Container * getParent();
		virtual void removeEventListener(int id);
		virtual void setParent(Container * parent);
		virtual void update(const float updateSpan);
	protected:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	private:
		struct EventListener {
			EventType type;
			std::function<void(Event *)> callback;
			bool useCapture;
		};
		std::map<int, EventListener> listeners;
		Container * parent;
		int idCount;
	};
}
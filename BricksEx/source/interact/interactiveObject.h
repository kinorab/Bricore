#pragma once

#include "../event.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <map>

namespace sf {
	class RenderTarget;
	class RenderStates;
}

namespace game {
	class Container;

	class InteractiveObject
		: public sf::Drawable,
		public sf::Transformable {
	public:
		InteractiveObject();
		virtual ~InteractiveObject();
		virtual int addEventListener(sf::Event::EventType type, std::function<void(Event *)> callback);
		virtual int addEventListener(sf::Event::EventType type, std::function<void(Event *)> callback, bool useCapture);
		virtual bool containsPoint(const sf::Vector2f & point) const = 0;
		virtual bool dispatchEvent(Event * event);
		virtual std::shared_ptr<sf::Drawable> getDrawable() const = 0;
		virtual Container * getParent();
		virtual void removeEventListener(int id);
		virtual void setParent(Container * parent);
	protected:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	private:
		struct EventListener {
			sf::Event::EventType type;
			std::function<void(Event *)> callback;
			bool useCapture;
		};
		std::map<int, EventListener> listeners;
		Container * parent;
		int idCount;
	};
}
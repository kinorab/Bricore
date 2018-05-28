#pragma once

#include "event.h"
#include <SFML/Graphics.hpp>
#include <functional>

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
		virtual std::weak_ptr<Container> getParent() const;
		virtual void initialize();
		virtual void removeEventListener(int id);
		virtual void setParent(std::weak_ptr<Container> parent);
	protected:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	private:
		struct EventListener {
			sf::Event::EventType type;
			std::function<void(Event *)> callback;
			bool useCapture;
		};
		std::map<int, EventListener> listeners;
		std::weak_ptr<Container> parent;
		int idCount;
	};
}
#pragma once

#include "../event/eventSubject.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Event;
}

namespace game {
	class Container;
	class UIEvent;

	class InteractiveObject :
		public EventSubject,
		public sf::Drawable {
	public:
		virtual ~InteractiveObject();
		using EventSubject::addListener;
		virtual bool containsPoint(const sf::Vector2f & point) const = 0;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const = 0;
		using EventSubject::dispatchEvent;
		virtual void dispatchEvent(UIEvent & event);
		virtual void dispatchEvent(UIEvent && event);
		virtual bool getEnabled() const;
		virtual Container * getParent();
		virtual void onDisabled();
		virtual void onEnabled();
		virtual void setEnabled(bool value);
		virtual void setParent(Container * parent);

	protected:
		InteractiveObject() noexcept;
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	private:
		bool bEnabled;
		Container * parent;
	};
}
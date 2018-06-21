#pragma once

#include "../event/eventSubject.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace sf {
	class RenderTarget;
	class RenderStates;
}

namespace game {
	class Container;
	class UIEvent;

	class InteractiveObject :
		public EventSubject,
		public sf::Drawable,
		public sf::Transformable {
	public:
		virtual ~InteractiveObject();
		using EventSubject::addListener;
		virtual int addListener(std::type_index eventType, std::shared_ptr<EventListener> listener);
		virtual bool containsPoint(const sf::Vector2f & point) const = 0;
		using EventSubject::dispatchEvent;
		virtual void dispatchEvent(UIEvent & event);
		virtual std::shared_ptr<sf::Drawable> getDrawable() const = 0;
		virtual bool getEnabled() const;
		virtual Container * getParent();
		virtual void onDisabled();
		virtual void onEnabled();
		virtual void setEnabled(bool value);
		virtual void setParent(Container * parent);
		virtual void update(const float updateRatio);
	protected:
		InteractiveObject();
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	private:
		bool enabled;
		Container * parent;
	};
}
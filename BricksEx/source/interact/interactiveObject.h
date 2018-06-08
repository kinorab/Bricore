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

	class InteractiveObject :
		public EventSubject,
		public sf::Drawable,
		public sf::Transformable {
	public:
		InteractiveObject();
		virtual ~InteractiveObject();
		virtual bool containsPoint(const sf::Vector2f & point) const = 0;
		virtual void dispatchEvent(Event * event) override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const = 0;
		virtual bool getEnabled() const;
		virtual Container * getParent();
		virtual void onDisabled();
		virtual void onEnabled();
		virtual void setEnabled(bool value);
		virtual void setParent(Container * parent);
		virtual void update(const float updateSpan);
	protected:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	private:
		bool enabled;
		Container * parent;
	};
}
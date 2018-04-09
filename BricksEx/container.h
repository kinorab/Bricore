#pragma once

#include "event.h"
#include <functional>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

namespace game {
	class Container :
		public std::enable_shared_from_this<Container>,
		public sf::Drawable,
		public sf::Transformable {
	public:
		Container();
		virtual ~Container() override;
		virtual void addChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements);
		virtual void addChildAt(const std::vector<std::shared_ptr<sf::Drawable>> & elements, size_t index);
		virtual void addEventListener(std::string type, std::function<void(Event *)> callback);
		virtual void addEventListener(std::string type, std::function<void(Event *)> callback, bool useCapture);
		virtual bool contains(const sf::Drawable * element) const;
		virtual bool containsPoint(const sf::Vector2f & point) const;
		virtual bool dispatchEvent(Event * event);
		virtual std::shared_ptr<sf::Drawable> getChildAt(int index) const;
		virtual int getChildIndex(const sf::Drawable * element) const;
		virtual int getChildrenCount() const;
		virtual std::weak_ptr<Container> getParent() const;
		virtual void initialize();
		virtual void removeAllChildren();
		virtual void removeChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements);
		virtual void removeChildAt(std::vector<int> indexes);
		virtual void removeChildren(int beginIndex, int endIndex);
		virtual void removeEventListener(std::string type, std::function<void(Event *)> callback, bool useCapture);
		virtual void setChildIndex(const sf::Drawable * element, int index);
		virtual void setParent(std::weak_ptr<Container> parent);
		virtual void swapChildren(const sf::Drawable * elementA, const sf::Drawable * elementB);
		virtual void swapChildrenAt(int indexA, int indexB);
	protected:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	private:
		struct EventListener;
		std::vector<std::shared_ptr<sf::Drawable>> children;
		std::vector<EventListener> listeners;
		std::weak_ptr<Container> parent;
	};
}

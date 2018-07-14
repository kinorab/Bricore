#pragma once

#include "circleShapeNode.h"
#include "drawableNode.h"
#include "rectangleShapeNode.h"
#include "spriteNode.h"
#include "vertexArrayNode.h"
#include <vector>
#include <memory>

namespace game {
	class Container :
		public std::enable_shared_from_this<Container>,
		public InteractiveObject {
	public:
		Container() noexcept;
		virtual ~Container() override;
		virtual void addChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements);
		virtual void addChildAt(const std::vector<std::shared_ptr<sf::Drawable>> & elements, const size_t index);
		virtual bool contains(const sf::Drawable * element) const;
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getChildAt(const int index) const;
		virtual size_t getChildIndex(const sf::Drawable * element) const;
		virtual std::shared_ptr<InteractiveObject> getChildNode(const sf::Drawable * element) const;
		virtual size_t getChildrenCount() const;
		virtual std::shared_ptr<InteractiveObject> getObjectUnderPoint(const sf::Vector2f & point);
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		virtual void removeAllChildren(const bool isRemoveChlidrenListener = false);
		// remove certain children and return their indexes
		virtual std::vector<int> removeChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements);
		virtual void removeChildAt(std::vector<int> indexes);
		virtual void removeChildren(const int beginIndex, const int endIndex);
		virtual void removeInvalidChildren();
		virtual void replaceChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements, const std::vector<int> indexes);
		virtual void setChildIndex(const sf::Drawable * element, const int index);
		virtual void swapChildren(const sf::Drawable * elementA, const sf::Drawable * elementB);
		virtual void swapChildrenAt(const int indexA, const int indexB);

	protected:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	private:
		std::vector<std::shared_ptr<InteractiveObject>> children;
	};
}

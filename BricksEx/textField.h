#pragma once

#include "UIComponent.h"

namespace game {
	class TextField
		: public std::enable_shared_from_this<Container>,
		public InteractiveObject {
	public:
		TextField(std::string text);
		virtual ~TextField();
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		virtual int getLength() const;
	protected:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	private:
		std::vector<std::shared_ptr<sf::Text>> content;
	};
}
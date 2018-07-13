#pragma once
#include "effectKind.h"
#include "../../interact/interactiveObject.h"
#include <SFML/Graphics/Sprite.hpp>

namespace game {
	class Attribute	
		: public EffectKind<Attribute>
		, public std::enable_shared_from_this<Attribute> 
		, public game::InteractiveObject {
	public:
		// for stable version release
		enum Kind {
			None,
			Flame,
			Ice,
			Thunder, 
			Darkness,
			Light,
			Poison,
		};
		explicit Attribute(const Kind element);
		explicit Attribute(const Kind element, const std::shared_ptr<sf::Texture> & texture);
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		void setPosition(const sf::Vector2f & position);
		void setPosition(const float x, const float y);
		void setOrigin(const sf::Vector2f & origin);
		void setOrigin(const float x, const float y);

		const sf::Vector2f & getPosition() const;
		sf::FloatRect getGlobalBounds() const;
		sf::FloatRect getLocalBounds() const;
		Attribute(const Attribute &) = delete;
		Attribute &operator =(const Attribute &) = delete;
		virtual ~Attribute();

		const Kind it;
		const AttributeEffect withEffect;

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

		const std::shared_ptr<sf::Sprite> context;
	};
}
#pragma once
#include "../../interact/interactiveObject.h"
#include <SFML/Graphics/Sprite.hpp>

namespace game {
	class Attribute	
		: public std::enable_shared_from_this<Attribute> 
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
		};
		explicit Attribute(const Kind element);
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

	private:
		static std::map<Kind, std::string> fileNames;

		std::unique_ptr<sf::Sprite> context;
	};
}
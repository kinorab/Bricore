#pragma once
#include "itemKind.h"
#include "../../interact/interactiveObject.h"
#include <SFML/Graphics/Sprite.hpp>

namespace item {
	class Chip :
		public ItemKind<Chip>
		, public std::enable_shared_from_this<Chip>
		, public game::InteractiveObject {
	public:
		explicit Chip(const Kind chip);
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		void setPosition(const sf::Vector2f & position);
		void setPosition(const float x, const float y);
		void setOrigin(const sf::Vector2f & origin);
		void setOrigin(const float x, const float y);

		const sf::Vector2f & getPosition() const;
		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;
		Chip(const Chip &) = delete;
		Chip & operator =(const Chip &) = delete;
		virtual ~Chip();

		const Kind it;

	private:
		static std::map<Kind, std::string> fileNames;

		std::unique_ptr<sf::Sprite> context;
	};
}
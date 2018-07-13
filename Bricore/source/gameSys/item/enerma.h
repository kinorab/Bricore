#pragma once
#include "itemKind.h"
#include "../../interact/interactiveObject.h"
#include <SFML/Graphics/Sprite.hpp>

namespace item {
	class Enerma :
		public ItemKind<Enerma>
		, public std::enable_shared_from_this<Enerma>
		, public game::InteractiveObject {
	public:
		explicit Enerma(const Kind enerma, const std::shared_ptr<sf::Texture> & texture);
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		void setAppear(const bool isAppear);
		void setPosition(const sf::Vector2f & position);
		void setPosition(const float x, const float y);
		void setOrigin(const sf::Vector2f & origin);
		void setOrigin(const float x, const float y);

		const sf::Vector2f & getPosition() const;
		sf::FloatRect getGlobalBounds() const;
		sf::FloatRect getLocalBonuds() const;
		Enerma(const Enerma &) = delete;
		Enerma & operator =(const Enerma &) = delete;
		virtual ~Enerma();

		const Kind it;

	private:
		const std::shared_ptr<sf::Sprite> context;
		bool bAppear;
	};
}
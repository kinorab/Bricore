#pragma once
#include "itemKind.h"
#include "../../interact/interactiveObject.h"
#include <SFML/Graphics/Sprite.hpp>

namespace item {
	class Core :
		public ItemKind<Core>
		, public std::enable_shared_from_this<Core>
		, public game::InteractiveObject {
	public:
		explicit Core(const Kind core);
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		void setOrigin(const sf::Vector2f & origin);
		void setOrigin(const float x, const float y);
		void setPosition(const sf::Vector2f & position);
		void setPosition(const float x, const float y);

		const sf::Vector2f & getPosition() const;
		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;
		Core(const Core &) = delete;
		Core & operator =(const Core &) = delete;
		virtual ~Core();

		const Kind it;

	private:
		static std::map<Kind, std::string> fileNames;

		std::unique_ptr<sf::Sprite> context;
	};
}
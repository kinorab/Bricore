#pragma once
#include "effectKind.h"
#include "../../interact/interactiveObject.h"
#include <SFML/Graphics/Sprite.hpp>

namespace game {
	class Effect :
		public EffectKind<Effect>
		, public std::enable_shared_from_this<Effect>
		, public game::InteractiveObject {
	public:
		// non context effect
		explicit Effect(const Kind effect, const bool isTargetItself);
		// context effect
		explicit Effect(const Kind effect, const std::shared_ptr<sf::Texture> & texture, const bool isTargetItself);
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		void setPosition(const sf::Vector2f & position);
		void setPosition(const float x, const float y);
		void setOrigin(const sf::Vector2f & origin);
		void setOrigin(const float x, const float y);

		const sf::Vector2f & getPosition() const;
		sf::FloatRect getGlobalBounds() const;
		sf::FloatRect getLocalBounds() const;
		Effect(const Effect &) = delete;
		Effect &operator =(const Effect &) = delete;
		virtual ~Effect();

		const Kind it;

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

		const std::shared_ptr<sf::Sprite> context;
		const bool bTargetItself;
	};
}
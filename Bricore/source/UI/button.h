#pragma once

#include "UIComponent.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

namespace sf {
	class Shape;
	class Time;
}

namespace game {
	class MouseMovedEvent;
	class MousePressedEvent;
	class MouseReleasedEvent;
	class Button
		: public std::enable_shared_from_this<Button>
		, public InteractiveObject {
	public:
		enum ButtonShape {
			Circle,
			Rectangle
		};
		// no special texture at release button
		explicit Button(const std::shared_ptr<sf::Texture> & upTexture
			, const std::shared_ptr<sf::Texture> & overTexture
			, const std::shared_ptr<sf::Texture> & downTexture
			, const ButtonShape shape);
		// special texture at release button
		explicit Button(const std::shared_ptr<sf::Texture> & upTexture
			, const std::shared_ptr<sf::Texture> & overTexture
			, const std::shared_ptr<sf::Texture> & downTexture
			, const std::shared_ptr<sf::Texture> & releaseTexture
			, const ButtonShape shape, const sf::Time & specialDuration);
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		void setSpecialEffectObacity(const sf::Uint8 a);
		virtual ~Button();

	protected:
		enum ButtonState {
			Up,
			Over,
			Down,
			Release
		};
		void onMouseEntered();
		void onMouseLeft();
		void onMousePressed(MousePressedEvent & event);
		void onMouseReleased(MouseReleasedEvent & event);

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		void initializeButton(const bool isReleaseSpecialize);
		void settleButtonSize(const std::shared_ptr<sf::Texture> & upTexture
			, const std::shared_ptr<sf::Texture> & overTexture
			, const std::shared_ptr<sf::Texture> & downTexture
			, const std::shared_ptr<sf::Texture> & releaseTexture);
		void settleButtonSize(const std::shared_ptr<sf::Texture> & upTexture
			, const std::shared_ptr<sf::Texture> & overTexture
			, const std::shared_ptr<sf::Texture> & downTexture);
		const ButtonShape buttonShape;
		bool bReleasing;
		ButtonState currentState;
		sf::Time specialDuration;
		sf::Clock clock;
		std::shared_ptr<sf::Shape> upObject;
		std::shared_ptr<sf::Shape> overObject;
		std::shared_ptr<sf::Shape> downObject;
		std::shared_ptr<sf::Shape> releaseObject;
	};
}
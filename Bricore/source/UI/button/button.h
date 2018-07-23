#pragma once
#include "../UIComponent.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

namespace game {
	class MouseMovedEvent;
	class MousePressedEvent;
	class MouseReleasedEvent;
	class Button
		: public std::enable_shared_from_this<Button>
		, public InteractiveObject {
	public:
		enum class State {
			Up,
			Over,
			Down,
			Release
		};
		enum class SpecialEffect {
			None,
		};
		virtual bool containsPoint(const sf::Vector2f & point) const = 0;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;

		bool isReleasing() const;
		State getState() const;
		virtual ~Button();

	protected:
		struct StateString {
			std::string buttonUp;
			std::string buttonOver;
			std::string buttonDown;
			std::string buttonRelease;
		};
		Button();
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const = 0;
		virtual void initialize() = 0;

		bool bReleasing;
		State currentState;
		sf::Clock clock;
	};
}
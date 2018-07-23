#pragma once
#include "button.h"

namespace game {
	class RectButton :
		public Button {
	public:
		enum Name {

		};
		explicit RectButton(const Name name);
		explicit RectButton(const Name name, const SpecialEffect effect, const sf::Time & duration);
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		void setSpecialEffect(const SpecialEffect effect, const sf::Time & duration);
		void setSpecialEffectObacity(const sf::Uint8 a);

		SpecialEffect getSpecialEffect() const;
		const sf::Time & getDuration() const;
		virtual ~RectButton();

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		virtual void initialize() override;
		void onMouseEntered();
		void onMouseLeft();
		void onMousePressed(MousePressedEvent & event);
		void onMouseReleased(MouseReleasedEvent & event);
		static std::map<Name, StateString> fileNames;

		sf::Time specialDuration;
		SpecialEffect currentEffect;
		std::map<State, std::shared_ptr<sf::RectangleShape>> rectButton;
	};
}
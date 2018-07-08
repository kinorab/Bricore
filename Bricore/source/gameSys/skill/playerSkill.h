#pragma once
#include "skillSystem.h"
#include "skillState.h"
#include "skillKind.h"
#include "../effect/effect.h"
#include "../effect/attribute.h"
#include <SFML/Window/Keyboard.hpp>
#include <map>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Texture;
	class Sprite;
}

namespace game {
	template<typename T> class SkillHandler;
	class EnergyBar;

	class PlayerSkill :
		public SkillSystem
		, public SkillKind<PlayerSkill>
		, public SkillState<PlayerSkill>
		, public std::enable_shared_from_this<PlayerSkill>
		, public sf::Drawable
		, public sf::Transformable {
		friend class SkillHandler<PlayerSkill>;
	public:
		explicit PlayerSkill(const Kind skillName, const sf::Time duration
			, const std::vector<Effect::Kind> &effects, const bool autoUse
			, const std::vector<Attribute::Kind> &attributes, const std::shared_ptr<EnergyBar> energyBar
			, const bool exist);
		void handleSkill(const sf::Event * const event) override;
		void handleSelect(const sf::Event * const event) override;
		void loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth = false);
		static void extendCarry(const size_t number);
		static void extendField(const size_t number);
		static void resetKey(const sf::Keyboard::Key useKey, const sf::Keyboard::Key swapKey);

		static size_t getMaxCarry();
		static size_t getCurrentCarry();
		static size_t getMaxOnField();
		static size_t getCurrentOnField();
		State getState() const;
		Kind getSkillName() const;
		virtual ~PlayerSkill();

	protected:
		struct SkillContent {
			State currentState;
			std::shared_ptr<sf::Sprite> context;
		};

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		void setState(const State state);
		void swapSkill(const std::shared_ptr<PlayerSkill> & other);

		static size_t uMaxCarry;
		static size_t uCurrentCarry;
		static size_t uMaxOnField;
		static size_t uCurrentOnField;
		static SkillHandler<PlayerSkill> handler;
		std::map<State, std::shared_ptr<sf::Texture>> statePreviews;
		std::shared_ptr<EnergyBar> energyBar;
		std::pair<Kind, SkillContent> skill;
	};
}

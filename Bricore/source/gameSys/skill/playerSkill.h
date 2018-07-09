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
			, std::vector<Effect::Kind> && effects, std::vector<Attribute::Kind> && attributes
			, const bool autoUse, const bool exist, const std::shared_ptr<EnergyBar> energyBar);
		virtual void initialize() override;
		virtual void handleSkill(const sf::Event * const event) override;
		virtual void handleSelect(const sf::Event * const event) override;
		void loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth = false);
		static void extendCarry(const size_t number);
		static void extendField(const size_t number);
		static void resetKey(const sf::Keyboard::Key playerSkill, const sf::Keyboard::Key playerSkillSwap
			, const sf::Keyboard::Key switchToPrevChargingSkill, const sf::Keyboard::Key switchToNextChargingSkill);

		static size_t getMaxCarry();
		static size_t getCurrentCarry();
		static size_t getMaxOnField();
		static size_t getCurrentOnField();
		bool isInitialize() const;
		State getState() const;
		Kind getSkillName() const;
		virtual ~PlayerSkill();

	protected:
		struct SkillContent {
			State currentState;
			std::shared_ptr<sf::Sprite> context;
		};
		struct SkillKey {
			sf::Keyboard::Key playerSkill;
			sf::Keyboard::Key playerSkillSwap;
			sf::Keyboard::Key switchToPrevChargingSkill;
			sf::Keyboard::Key switchToNextChargingSkill;
		};
	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		void setState(const State state);
		void swapSkill(const std::shared_ptr<PlayerSkill> & other);
		static size_t uMaxCarry;
		static size_t uCurrentCarry;
		static size_t uMaxOnField;
		static size_t uCurrentOnField;
		static SkillKey key;
		static SkillHandler<PlayerSkill> handler;
		bool bInitialize;
		std::map<State, std::shared_ptr<sf::Texture>> statePreviews;
		std::pair<Kind, SkillContent> skill;
		std::shared_ptr<EnergyBar> m_energyBar;
	};
}

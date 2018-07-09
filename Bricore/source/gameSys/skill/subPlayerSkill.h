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

	class SubPlayerSkill :
		public SkillSystem
		, public SkillKind<SubPlayerSkill>
		, public SkillState<SubPlayerSkill>
		, public std::enable_shared_from_this<SubPlayerSkill>
		, public sf::Drawable
		, public sf::Transformable {
		friend class SkillHandler<SubPlayerSkill>;
	public:
		explicit SubPlayerSkill(const Kind skillName, const sf::Time duration
			, std::vector<Effect::Kind> && effects, std::vector<Attribute::Kind> && attributes
			, const bool autoUse, const bool exist, const std::shared_ptr<EnergyBar> energyBar);
		virtual void initialize() override;
		virtual void handleSkill(const sf::Event * const event) override;
		virtual void handleSelect(const sf::Event * const event) override;
		void loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth = false);
		static void extendCarry(const size_t number);
		static void extendField(const size_t number);
		static void resetKey(const sf::Keyboard::Key subSkill, const sf::Keyboard::Key subSkillSwap
			, const sf::Keyboard::Key turnSkillToTypeSkill, const sf::Keyboard::Key switchToPrevChargingSkill
			, const sf::Keyboard::Key switchToNextChargingSkill);

		static size_t getMaxCarry();
		static size_t getCurrentCarry();
		static size_t getMaxOnField();
		static size_t getCurrentOnField();
		bool isInitialize() const;
		State getState() const;
		Kind getSkillName() const;
		virtual ~SubPlayerSkill();

	protected:
		struct SkillContent {
			State currentState;
			std::shared_ptr<sf::Sprite> context;
		};
		struct SkillKey {
			sf::Keyboard::Key subSkill;
			sf::Keyboard::Key subSkillSwap;
			sf::Keyboard::Key turnSkillToTypeSkill;
			sf::Keyboard::Key switchToPrevChargingSkill;
			sf::Keyboard::Key switchToNextChargingSkill;
		};

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		void setState(const State state);
		void swapSkill(const std::shared_ptr<SubPlayerSkill> &other);
		static size_t uMaxCarry;
		static size_t uCurrentCarry;
		static size_t uMaxOnField;
		static size_t uCurrentOnField;
		static SkillKey key;
		static SkillHandler<SubPlayerSkill> handler;
		bool bInitialize;
		bool bTypeSkill;
		std::map<State, std::shared_ptr<sf::Texture>> statePreviews;
		std::shared_ptr<EnergyBar> energyBar;
		std::pair<Kind, SkillContent> skill;
	};
}

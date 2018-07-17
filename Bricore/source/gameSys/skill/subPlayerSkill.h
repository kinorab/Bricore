#pragma once
#include "../../interact/interactiveObject.h"
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
		, public InteractiveObject {
		friend class SkillHandler<SubPlayerSkill>;
	public:
		explicit SubPlayerSkill(const Kind skillName, const sf::Time duration
			, std::vector<std::pair<Effect::Kind, bool>> && effects, std::vector<Attribute::Kind> && attributes
			, const bool autoUse, const bool exist, const std::shared_ptr<EnergyBar> energyBar);
		virtual void initialize() override;
		virtual void update() override;
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
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
			Kind name;
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
		void onKeyPressed(KeyPressedEvent & event);
		void onMousePressed(MousePressedEvent & event);
		void onGameFinishedLevel(GameFinishedLevelEvent & event);

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		void setState(const State nextState);
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
		SkillContent skill;
		std::shared_ptr<EnergyBar> m_energyBar;
	};
}

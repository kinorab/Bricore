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

	class BallSkill :
		public SkillSystem
		, public SkillKind<BallSkill>
		, public SkillState<BallSkill>
		, public std::enable_shared_from_this<BallSkill>
		, public sf::Drawable
		, public sf::Transformable {
		friend class SkillHandler<BallSkill>;
	public:
		explicit BallSkill(const Kind skillName, const sf::Time duration
			, const std::vector<Effect::Kind> &effects
			, const std::vector<Attribute::Kind> &attributes = { Attribute::None }, const bool autoUse = false);
		virtual void handleSkill(const sf::Event * const event) override;
		virtual void handleSelect(const sf::Event * const event) override;
		void loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth = false);
		static void loadFrame(const std::vector<std::string> &fileName, const bool isSmooth = false);
		static void extendField(size_t number);
		static void extendDropping(size_t number);
		static void resetKey(const sf::Keyboard::Key useKey, const sf::Keyboard::Key swapKey);

		static size_t getMaxDropping();
		static size_t getCurrentCarry();
		static size_t getMaxOnField();
		static size_t getCurrentOnField();
		State getState() const;
		Kind getSkillName() const;
		virtual ~BallSkill();
	protected:
		struct SkillContent {
			State currentState;
			std::shared_ptr<sf::Sprite> frame;
			std::shared_ptr<sf::Sprite> context;
		};

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		void setState(const State state);
		void swapSkill(const std::shared_ptr<BallSkill> other);

		static size_t uMaxDropping;
		static size_t uCurrentCarry;
		static size_t uMaxOnField;
		static size_t uCurrentOnField;
		static std::map<std::string, std::shared_ptr<sf::Texture>> framePreviews;
		static SkillHandler<BallSkill> handler;
		std::map<State, std::shared_ptr<sf::Texture>> statePreviews;
		std::pair<Kind, SkillContent> skill;
	};
}

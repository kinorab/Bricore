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

	class BallSkill :
		public SkillSystem
		, public SkillKind<BallSkill>
		, public SkillState<BallSkill>
		, public std::enable_shared_from_this<BallSkill>
		, public InteractiveObject {
		friend class SkillHandler<BallSkill>;
	public:
		explicit BallSkill(const Kind skillName, const sf::Time duration
			, std::vector<std::pair<Effect::Kind, bool>> && effects, std::vector<Attribute::Kind> && attributes
			, const bool autoUse, const bool exist);
		virtual void initialize() override;
		virtual void update() override;
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		void loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth = false);
		static void loadFrame(const std::vector<std::string> &fileName, const bool isSmooth = false);
		static void extendField(size_t number);
		static void extendDropping(size_t number);
		static void resetKey(const sf::Keyboard::Key ballSkill, const sf::Keyboard::Key ballSkillSwap);

		static size_t getMaxDropping();
		static size_t getCurrentCarry();
		static size_t getMaxOnField();
		static size_t getCurrentOnField();
		bool isInitialize() const;
		State getState() const;
		Kind getSkillName() const;
		virtual ~BallSkill();

	protected:
		struct SkillContent {
			Kind name;
			State currentState;
			std::shared_ptr<sf::Sprite> frame;
			std::shared_ptr<sf::Sprite> context;
		};
		struct SkillKey {
			sf::Keyboard::Key ballSkill;
			sf::Keyboard::Key ballSkillSwap;
		};
		void onKeyPressed(KeyPressedEvent & event);
		void onMousePressed(MousePressedEvent & event);
		void onGameFinishedLevel(GameFinishedLevelEvent & event);

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		void setState(const State nextState);
		void swapSkill(const std::shared_ptr<BallSkill> & other);

		static size_t uMaxDropping;
		static size_t uCurrentCarry;
		static size_t uMaxOnField;
		static size_t uCurrentOnField;
		static std::map<std::string, std::shared_ptr<sf::Texture>> framePreviews;
		static SkillKey key;
		static SkillHandler<BallSkill> handler;
		bool bInitialize;
		std::map<State, std::shared_ptr<sf::Texture>> statePreviews;
		SkillContent skill;
	};
}

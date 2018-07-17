#pragma once
#include "../../interact/interactiveObject.h"
#include "skillSystem.h"
#include "skillKind.h"
#include "skillState.h"
#include "../effect/effect.h"
#include "../effect/attribute.h"
#include <vector>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Sprite;
	class Texture;
	class Event;
}

namespace game {
	template<typename T> class SkillHandler;
	class RageBar;

	class BossSkill :
		public SkillSystem
		, public SkillKind<BossSkill>
		, public SkillState<BossSkill>
		, public std::enable_shared_from_this<BossSkill>
		, public InteractiveObject {
		friend class SkillHandler<BossSkill>;
	public:
		explicit BossSkill(const Kind skillName, const sf::Time &duration
			, std::vector<std::pair<Effect::Kind, bool>> && effects, std::vector<Attribute::Kind> && attributes
			, const bool exist, const std::shared_ptr<RageBar> rageBar);
		virtual void initialize() override;
		virtual void update() override;
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		void loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth = false);

		bool isInitialize() const;
		State getState() const;
		Kind getSkillName() const;
		virtual ~BossSkill();

	protected:
		struct SkillContent {
			Kind name;
			State currentState;
			// preview for information showed on screen
			std::shared_ptr<sf::Sprite> preview;
		};
		void onGameFinishedLevel(GameFinishedLevelEvent & event);

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		void setState(const State nextState);

		static SkillHandler<BossSkill> handler;
		bool bInitialize;
		std::map<State, std::shared_ptr<sf::Texture>> statePreviews;
		SkillContent skill;
		std::shared_ptr<RageBar> m_rageBar;
	};
}
#pragma once
#include "skillKind.h"
#include "skillState.h"
#include "skillSystem.h"
#include "../../interact/interactiveObject.h"
#include <vector>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Sprite;
}

namespace game {
	template<typename T> class SkillHandler;
	class Boss;
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
			, const bool exist, const std::shared_ptr<RageBar> rageBar, const Boss * boss);
		virtual void initialize() override;
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;

		bool isInitialize() const;
		State getState() const;
		Kind getSkillName() const;
		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;
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
		virtual void update() override;
		void setState(const State nextState);

		static SkillHandler<BossSkill> handler;
		static std::map<Kind, std::map<State, std::string>> fileNames;
		bool bInitialize;
		SkillContent skill;
		std::shared_ptr<RageBar> m_rageBar;
		const Boss * c_boss;
	};
}
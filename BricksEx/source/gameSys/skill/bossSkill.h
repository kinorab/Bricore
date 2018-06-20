#pragma once
#include "skillSystem.h"
#include "skillKind.h"
#include "skillState.h"
#include "../effect/effect.h"
#include "../effect/attribute.h"
#include <memory>
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

	class BossSkill :
		public SkillSystem
		, public SkillKind<BossSkill>
		, public SkillState<BossSkill>
		, public std::enable_shared_from_this<BossSkill>
		, public sf::Drawable
		, public sf::Transformable {
		friend class SkillHandler<BossSkill>;
	public:
		explicit BossSkill(const Kind skillName, const sf::Time &duration
			, const std::vector<Effect::Kind> &effects
			, const std::vector<Attribute::Kind> &attributes = { Attribute::None });
		virtual void handleSkill(const sf::Event * const event) override;
		virtual void handleSelect(const sf::Event * const event) override;
		virtual void loadPreview(const std::string &fileName);

		virtual State getState() const;
		virtual Kind getSkillName() const;
		virtual ~BossSkill();
	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		virtual void setState(const State state);

		std::shared_ptr<sf::Texture> cache;
		struct Content {
			State currentState;
			std::shared_ptr<sf::Sprite> preview;
		};
		std::pair<Kind, Content> skill;
		static SkillHandler<BossSkill> handler;
	};
}
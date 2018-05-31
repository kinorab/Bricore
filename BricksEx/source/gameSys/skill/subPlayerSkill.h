#pragma once
#include "skillSystem.h"
#include "../effect/effect.h"
#include <map>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Texture;
	class Sprite;
}

namespace game {
	class SubPlayerSkill :
		public SkillSystem
		, public sf::Drawable
		, public sf::Transformable {
	public:
		enum class SkillState {
			None,			// no appear on stage
			OnField,		// on subPlayer skill field
			Using,			// when using it
			Locked			// may be locked by outside effect(stage area, boss skill etc...), cannot be used or swapped
		};
		explicit SubPlayerSkill(const SubPlayer skillName, const std::vector<NormalEffect> &normalEffects, const sf::Time &duration, const bool autoUse = false);
		virtual void swapSkill(SubPlayerSkill &other);
		virtual void useSkill() override;
		virtual size_t upgradeSkill() override;
		virtual void loadPreviewFile(const std::map<SkillState, std::string> &fileName, const bool isSmooth = false);
		virtual void setState(const SkillState state);

		virtual SkillState getState() const;
		virtual SubPlayer getSkillName() const;
		virtual ~SubPlayerSkill();

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		virtual void handleSkill() override;

		std::map<SkillState, std::shared_ptr<sf::Texture>> statePreviews;
		struct Picture {
			SkillState currentState;
			std::shared_ptr<sf::Sprite> context;
		};
		std::pair<SubPlayer, Picture> skill;
	};
}

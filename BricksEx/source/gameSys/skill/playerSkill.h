#pragma once
#include "skillSystem.h"
#include "../effect/effectSystem.h"
#include <map>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Texture;
	class Sprite;
}

namespace game {
	class PlayerSkill :
		public SkillSystem
		, public sf::Drawable
		, public sf::Transformable {
	public:
		enum class SkillState {
			None,			// no appear on stage
			OnMiniField,	// on player skill smaller field
			OnField,		// on player skill field
			Using,			// when using it
			Locked			// may be locked by outside effect(stage area, boss skill etc...), cannot be used or swapped
		};
		explicit PlayerSkill(const Player skillName, const std::vector<Normal> &normalEffects, const sf::Time &duration, const bool autoUse = false);
		virtual void swapSkill(PlayerSkill &other);
		virtual void handleSkill(const sf::Event * const event) override;
		virtual void handleSelect(const sf::Event * const event) override;
		virtual void extendCarry(const size_t number);
		virtual size_t upgradeSkill() override;
		virtual void loadPreviewFile(const std::map<SkillState, std::string> &fileName, const bool isSmooth = false);
		virtual void setState(const SkillState state);

		virtual size_t getMaximumCarry() const;
		virtual size_t getCurrentCarry() const;
		virtual SkillState getState() const;
		virtual Player getSkillName() const;
		virtual ~PlayerSkill();

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

		std::map<SkillState, std::shared_ptr<sf::Texture>> statePreviews;
		struct Picture {
			SkillState currentState;
			std::shared_ptr<sf::Sprite> context;
		};
		std::pair<Player, Picture> skill;
		// maximum skill's carrying capacity in every level
		static size_t maximumCarry;
		static size_t currentCarry;
	};
}

#pragma once
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include "skill.h"

namespace game {
	class PlayerSkill : public Skill {
	public:
		explicit PlayerSkill(const Player skillName, const sf::Time &duration, const bool autoUse = false);
		virtual void useSkill() override;
		virtual void upgradeSkill() override;
		virtual void gainSkill(const Player skillName);
		virtual Player getSkillName() const;
		virtual const sf::Sprite & getSkill() const;
		virtual ~PlayerSkill();

	protected:
		virtual void handleSkill() override;

	private:
		enum class SkillState {
			None,			// no appear on stage
			OnMiniField,	// on player skill smaller field
			OnField,		// on player skill field
			Using,			// when using it
			Locked			// may be locked by outside effect(stage area, boss skill etc...), cannot be used or swapped
		};
		SkillState currentState;
		Player skillName;
		std::map<SkillState, sf::Texture> skillPicture;
		sf::Sprite skill;
	};
}

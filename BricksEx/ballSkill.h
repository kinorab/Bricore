#pragma once
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include "skill.h"

namespace game {
	class BallSkill : public Skill {
	public:
		explicit BallSkill(const Ball skillName, const sf::Time &duration, const bool autoUse = false);
		virtual void useSkill() override;
		virtual void upgradeSkill() override;
		virtual void gainSkill(const Ball skillName);
		virtual void setFrame(const size_t skillLevel);
		virtual Ball getSkillName() const;
		virtual const sf::Sprite & getSkill() const;
		virtual ~BallSkill();

	protected:
		virtual void handleSkill() override;

	private:
		static std::vector<sf::Image> frame;
		enum class SkillState {
			No_Buy,			// still on store
			None,			// no appear on stage
			OnDropping,		// drop from brick
			OnMiniField,	// on ball skill smaller field
			OnField,		// on ball skill field
			Using,			// when using it
			Locked			// may be locked by outside effect(stage area, boss skill etc...), cannot be used or swapped
		};
		SkillState currentState;
		std::map<SkillState, sf::Texture> skillPicture;
		Ball skillName;
		sf::Sprite skill;
	};
}

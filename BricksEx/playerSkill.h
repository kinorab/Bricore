#pragma once
#include "skill.h"

namespace game {
	class PlayerSkill : public Skill {
	public:
		explicit PlayerSkill(const Player skill, const sf::Time &duration, const bool autoUse = false);
		virtual void gainSkill(const Player skill);
		virtual ~PlayerSkill();
	private:
		Player skill;
	};
}

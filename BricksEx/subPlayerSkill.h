#pragma once
#include "skill.h"

namespace game {
	class SubPlayerSkill : public Skill {
	public:
		explicit SubPlayerSkill(const SubPlayer skill, const sf::Time &duration, const bool autoUse = false);
		virtual void gainSkill(const SubPlayer skill);
		virtual ~SubPlayerSkill();
	private:
		SubPlayer skill;
	};
}

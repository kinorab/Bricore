#pragma once
#include "skill.h"

namespace game {
	class BallSkill : public Skill {
	public:
		explicit BallSkill(const Ball skill, const sf::Time &duration, const bool autoUse = false);
		virtual void gainSkill(const Ball skill);
		virtual ~BallSkill();
	private:
		Ball skill;
	};
}

#pragma once

namespace game {
	class PlayerSkill;
	class SubPlayerSkill;
	class BallSkill;
	class BossSkill;
	template<typename T> class SkillKind;

	template<> class SkillKind<PlayerSkill> {
	public:
		enum Kind {
			AmbitGuard,
			DropRateUp,
			EnergyRush,
		};
	};

	template<> class SkillKind<SubPlayerSkill> {
	public:
		// skill difference with subPlayer's type
		enum Kind {
			EnergyRush,
			ForceField,
			ForceShield,
			InfinitePower,
			MagicalField,
			MagicalShield,
		};
	};

	template<> class SkillKind<BallSkill> {
	public:
		enum Kind {
			HugeBody,
			IronBody,
			MultipleAttack,
			ShieldGuard,
			ShuttleSpace,
		};
	};

	template<> class SkillKind<BossSkill> {
	public:
		enum Kind {
			MultipleShoot,
		};
	};
}

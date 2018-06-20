#pragma once

namespace game {
	class PlayerSkill;
	class SubPlayerSkill;
	class BallSkill;
	class BossSkill;
	template<typename T> class SkillState;

	template<> class SkillState<PlayerSkill> {
	public:
		enum State {
			OnCharging,		// charged by energy bar
			OnFirstField,	// on player first skill field
			OnSecondField,	// on player second skill field
			OnThirdField,	// on player third skill field
			OnFourthField,	// on player fourth skill field
			None = 100,		// no appear on stage
			Using			// when using it
		};
		static const State maxField = OnFourthField;
	};
	template<> class SkillState<SubPlayerSkill> {
	public:
		enum State {
			OnCharging,		// charged by energy bar
			OnFirstField,	// on subplayer first skill field
			OnSecondField,	// on subplayer second skill field
			OnThirdField,	// on subplayer third skill field
			None = 100,		// no appear on stage
			Using			// when using it
		};
		static const State maxField = OnThirdField;
	};
	template<> class SkillState<BallSkill> {
	public:
		enum State {
			OnDropping,		// drop from brick
			OnFirstField,	// on ball first skill field
			OnSecondField,	// on ball second skill field
			OnThirdField,	// on ball third skill field
			OnFourthField,	// on ball fourth skill field
			None = 100,		// no appear on stage
			Using,			// when using it
		};
		static const State maxField = OnFourthField;
	};
	template<> class SkillState<BossSkill> {
	public:
		enum State {
			None,
			Using
		};
	};
}
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
			Waiting = 100,	// waiting on stage
			Using,			// when using it
			Display,		// display on store, illustration etc..
			Prepare			// on prepare area to be select
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
			OnFourthField,	// on subplayer fourth skill field
			Waiting = 100,	// waiting on stage
			Using,			// when using it
			Display,		// display on store, illustration etc..
			Prepare			// on prepare area to be select
		};
		static const State maxField = OnFourthField;
	};
	template<> class SkillState<BallSkill> {
	public:
		enum State {
			OnDropping,		// drop from brick
			OnFirstField,	// on ball first skill field
			OnSecondField,	// on ball second skill field
			OnThirdField,	// on ball third skill field
			OnFourthField,	// on ball fourth skill field
			Waiting = 100,	// waiting on stage
			Using,			// when using it
			Display,		// display on store, illustration etc..
			Prepare			// on prepare area to be select
		};
		static const State maxField = OnFourthField;
	};
	template<> class SkillState<BossSkill> {
	public:
		enum State {
			Waiting,		// waiting for use
			Using,			// when using it
			Display			// display on information to let player know, illustration etc..
		};
	};
}

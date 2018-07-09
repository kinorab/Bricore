#pragma once
#include "bossSkill.h"
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <map>

namespace game {
	template<typename T> class SkillState;

	template<typename T>
	class SkillHandler {
		using State = typename SkillState<T>::State;
	public:
		SkillHandler();
		// insert a skill record
		void insert(const std::shared_ptr<T> skill);
		// remove a skill record
		void remove(const std::shared_ptr<T> skill);
		// when state is none
		// return true will appear on screen
		bool tryAppear(const std::shared_ptr<T> skill);
		// when state is:
		// ball: onDropping
		// (sub)player: onCharging
		// return true will move to waiting field
		bool tryEnterField(const std::function<void(const State)> &callback);
		// when state is onField
		// return true will move to nearer field
		bool tryForward(const State currentState, const std::function<void (const State)> &callback);
		// return true if swap successfully
		// false will warn user
		bool trySwap();
		~SkillHandler() = default;

	private:
		std::multimap<State, std::shared_ptr<T>> skillRecords;
	};
	template<>
	bool SkillHandler<BossSkill>::tryEnterField(const std::function<void(const SkillState<BossSkill>::State)>&) = delete;
	template<>
	bool SkillHandler<BossSkill>::tryForward(const State, const std::function<void(const SkillState<BossSkill>::State)> &) = delete;
	template<>
	bool SkillHandler<BossSkill>::trySwap() = delete;
}

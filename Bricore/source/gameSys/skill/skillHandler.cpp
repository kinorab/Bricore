#include "skillHandler.h"
#include "playerSkill.h"
#include "subPlayerSkill.h"
#include "ballSkill.h"
#include <algorithm>
#include <stdexcept>

using namespace game;

template class SkillHandler<PlayerSkill>;
template class SkillHandler<SubPlayerSkill>;
template class SkillHandler<BallSkill>;
template class SkillHandler<BossSkill>;

template<typename T>
SkillHandler<T>::SkillHandler() {
}

template<typename T>
void SkillHandler<T>::insert(const std::shared_ptr<T> skill) {
	skillRecords.emplace(skill->skill.second.currentState, skill);
}

template<typename T>
void SkillHandler<T>::remove(const std::shared_ptr<T> skill) {
	for (auto iter = skillRecords.begin(); iter != skillRecords.end(); ++iter) {
		if (iter->second != skill) continue;
		skillRecords.erase(iter);
		return;
	}
	throw std::exception("Skill no records");
}

template<>
bool SkillHandler<PlayerSkill>::tryAppear(const std::shared_ptr<PlayerSkill> skill) {
	if (skillRecords.count(State::OnCharging) == 0) {
		skill->setState(State::OnCharging);
		return true;
	}
	return false;
}

template<>
bool SkillHandler<SubPlayerSkill>::tryAppear(const std::shared_ptr<SubPlayerSkill> skill) {
	if (skillRecords.count(State::OnCharging) == 0) {
		skill->setState(State::OnCharging);
		return true;
	}
	return false;
}

template<>
bool SkillHandler<BallSkill>::tryAppear(const std::shared_ptr<BallSkill> skill) {
	if (skillRecords.count(State::OnDropping) <= skill->uMaxDropping) {
		skill->setState(State::OnDropping);
		return true;
	}
	return false;
}

template<>
bool SkillHandler<BossSkill>::tryAppear(const std::shared_ptr<BossSkill> skill) {
	if (skillRecords.count(State::Using) == 0) {
		skill->setState(State::Using);
		return true;
	}
	return false;
}

template<typename T>
bool SkillHandler<T>::tryEnterField(const std::function<void(const State)>& callback) {
	for (size_t i = T::uMaxOnField; i >= 1; --i) {
		State field = static_cast<State>(i);
		if (skillRecords.count(field) == 0) {
			callback(field);
			return true;
		}
		else if (!skillRecords.find(field)->second->bLocked) return false;
	}
	return false;
}

template<typename T>
bool SkillHandler<T>::tryForward(const State currentState, const std::function<void (const State)> &callback) {
	const size_t maxField = T::uMaxOnField;
	const size_t currentNumber = static_cast<size_t>(currentState);
	if (currentNumber > maxField || currentNumber == 0) throw std::out_of_range("State is not onField.");
	for (size_t i = currentNumber - 1; i > 0; --i) {
		State field = static_cast<State>(i);
		if (skillRecords.count(field) == 0) {
			callback(field);
			return true;
		}
		else if (!skillRecords.find(field)->second->bLocked) return false;
	}
	return false;
}

template<typename T>
bool SkillHandler<T>::trySwap() {
	auto firstField = skillRecords.find(State::OnFirstField);
	auto secondField = skillRecords.find(State::OnSecondField);
	if (firstField == skillRecords.end()
		|| secondField == skillRecords.end()
		|| firstField->second->bLocked
		|| secondField->second->bLocked) return false;
	firstField->second->swapSkill(secondField->second);
	return true;
}

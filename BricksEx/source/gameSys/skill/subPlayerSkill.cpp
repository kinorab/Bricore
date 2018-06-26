#include "subPlayerSkill.h"
#include "skillHandler.h"
#include "../effect/entireEffect.h"
#include "../../definition/gameState.h"
#include <SFML/Graphics.hpp>

using namespace game;

size_t SubPlayerSkill::maxCarry(1);
size_t SubPlayerSkill::currentCarry(0);
size_t SubPlayerSkill::maxOnField(2);
size_t SubPlayerSkill::currentOnField(0);
SkillHandler<SubPlayerSkill> SubPlayerSkill::handler;

SubPlayerSkill::SubPlayerSkill(const Kind skillName, const sf::Time duration
	, const std::vector<Effect::Kind> &effects
	, const std::vector<Attribute::Kind> &attributes, const bool autoUse)
	: skill(skillName, Content{ State::None, nullptr })
	, SkillSystem(duration, autoUse) {
	std::for_each(effects.begin(), effects.end(), [&](const Effect::Kind effect) {
		skillEffects.push_back(std::shared_ptr<EntireEffect>(new EntireEffect(effect, this)));
	});
	std::for_each(attributes.begin(), attributes.end(), [&](const Attribute::Kind element) {
		skillAttributes.push_back(std::shared_ptr<Attribute>(new Attribute(element)));
	});
	handler.insert(shared_from_this());
}

void SubPlayerSkill::handleSkill(const sf::Event * const event) {
	if (status != Status::Selected || game::currentState == GameState::LEVEL_FINISHED) return;
	using namespace std::placeholders;
	State currentState = skill.second.currentState;
	switch (currentState) {
	case State::OnCharging:
		if (/*!energyBar.full() ||*/locked) break;
		if (handler.tryEnterField(std::bind(&SubPlayerSkill::setState, this, _1))) {
			// energyBar.clear();
		}
		break;
	case State::OnFirstField:
		if (silenced) break;
		if (event->key.code == handler.useKey || autoUse) setState(State::Using);
		break;
	case State::OnSecondField:
		if (locked) break;
		handler.tryForward(currentState, std::bind(&SubPlayerSkill::setState, this, _1));
		break;
	case State::OnThirdField:
		if (locked) break;
		handler.tryForward(currentState, std::bind(&SubPlayerSkill::setState, this, _1));
		break;
	case State::None:
		handler.tryAppear(shared_from_this());
		break;
	case State::Using:
		useSkill();
		if (elapsed()) {
			exhausted();
			setState(State::None);
		}
		break;
	default:
		throw std::exception("Some bug in handleSkill.");
		break;
	}
	if (event->type != sf::Event::KeyPressed) return;
	if (event->key.code == handler.swapKey) {
		if (handler.trySwap()) {
		}
		else {
		}
	}
}

void SubPlayerSkill::handleSelect(const sf::Event * const event) {
	if (status == Status::None || event->type != sf::Event::MouseButtonPressed || game::currentState != GameState::LEVEL_FINISHED) return;
	if (skill.second.context->getGlobalBounds().contains(getTransform().getInverse().transformPoint(
		static_cast<float>(event->mouseButton.x), static_cast<float>(event->mouseButton.y)))) {
		if (currentCarry < maxCarry && selectOn()) {
			++currentCarry;
			return;
		}
		if (selectOff()) {
			--currentCarry;
			return;
		}
	}
}

void SubPlayerSkill::loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::pair<State, std::string> &file) {
		statePreviews.emplace(file.first, std::shared_ptr<sf::Texture>(new sf::Texture));
		statePreviews.at(file.first)->loadFromFile(file.second);
		statePreviews.at(file.first)->setSmooth(isSmooth);
	});
}

void SubPlayerSkill::extendCarry(const size_t number) {
	maxCarry += number;
}

void SubPlayerSkill::extendField(const size_t number) {
	if (number + maxOnField > static_cast<size_t> (maxField)) {
		throw std::out_of_range("Excess max field number");
	}
	maxOnField += number;
}

void SubPlayerSkill::resetKey(const sf::Keyboard::Key useKey, const sf::Keyboard::Key swapKey){
	handler.useKey = useKey;
	handler.swapKey = swapKey;
}

void SubPlayerSkill::setState(const State state) {
	if (skill.second.currentState == State::OnCharging) {
		if (currentOnField > maxOnField) throw std::invalid_argument("Too many skills on field.");
		++currentOnField;
	}
	else if (state == State::Using) {
		if (currentOnField == 0) throw std::invalid_argument("Field not have any skills.");
		--currentOnField;
	}
	skill.second.currentState = state;
	skill.second.context.reset(new sf::Sprite(*statePreviews.at(state)));
}

void SubPlayerSkill::swapSkill(const std::shared_ptr<SubPlayerSkill> other) {
	State state = skill.second.currentState;
	State inputState = other->skill.second.currentState;
	statePreviews.swap(other->statePreviews);
	skill.swap(other->skill);
	setState(inputState);
	other->setState(state);
}

size_t SubPlayerSkill::getMaxCarry() {
	return maxCarry;
}

size_t SubPlayerSkill::getCurrentCarry() {
	return currentCarry;
}

size_t SubPlayerSkill::getMaxOnField() {
	return maxOnField;
}

size_t SubPlayerSkill::getCurrentOnField() {
	return currentOnField;
}

SubPlayerSkill::State SubPlayerSkill::getState() const {
	return skill.second.currentState;
}

SkillKind<SubPlayerSkill>::Kind SubPlayerSkill::getSkillName() const {
	return skill.first;
}

SubPlayerSkill::~SubPlayerSkill() {
}

void SubPlayerSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (skill.second.currentState == State::None) return;
	states.transform *= getTransform();
	target.draw(*skill.second.context, states);
}

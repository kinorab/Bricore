#include "playerSkill.h"
#include "skillHandler.h"
#include "../effect/entireEffect.h"
#include "../bar/energyBar.h"
#include "../../definition/gameState.h"
#include <SFML/Graphics.hpp>

using namespace game;

size_t PlayerSkill::uMaxCarry(3);
size_t PlayerSkill::uCurrentCarry(0);
size_t PlayerSkill::uMaxOnField(2);
size_t PlayerSkill::uCurrentOnField(0);
SkillHandler<PlayerSkill> PlayerSkill::handler;
PlayerSkill::SkillKey PlayerSkill::key;

PlayerSkill::PlayerSkill(const Kind skillName, const sf::Time duration
	, std::vector<Effect::Kind> && effects, std::vector<Attribute::Kind> && attributes
	, const bool autoUse, const bool exist, const std::shared_ptr<EnergyBar> energyBar)
	: skill(skillName, SkillContent{ State::None, nullptr })
	, SkillSystem(duration, autoUse, exist)
	, m_energyBar(std::move(energyBar))
	, bInitialize(false) {
	std::for_each(effects.begin(), effects.end(), [&](const Effect::Kind effect) {
		skillEffects.push_back(std::make_shared<EntireEffect>(effect, this));
	});
	std::for_each(attributes.begin(), attributes.end(), [&](const Attribute::Kind element) {
		skillAttributes.push_back(std::make_shared<Attribute>(element));
	});
}

void PlayerSkill::initialize() {
	if (bInitialize) return;
	handler.insert(shared_from_this());
	bInitialize = true;
}

void PlayerSkill::handleSkill(const sf::Event * const event) {
	if (status != Status::Selected || currentState == GameState::LEVEL_FINISHED) return;
	using namespace std::placeholders;
	State currentState = skill.second.currentState;
	switch (currentState) {
	case State::OnCharging:
		if (!m_energyBar->isFull() || bLocked) break;
		if (handler.tryEnterField(std::bind(&PlayerSkill::setState, this, _1))) {
			m_energyBar->clear();
		}
		break;
	case State::OnFirstField:
		if (bSilenced) break;
		if (event->key.code == key.playerSkill || bAutoUse) setState(State::Using);
		break;
	case State::OnSecondField:
		if (bLocked) break;
		if (handler.tryForward(currentState, std::bind(&PlayerSkill::setState, this, _1))) {}
		break;
	case State::OnThirdField:
		if (bLocked) break;
		if (handler.tryForward(currentState, std::bind(&PlayerSkill::setState, this, _1))) {}
		break;
	case State::OnFourthField:
		if (bLocked) break;
		if (handler.tryForward(currentState, std::bind(&PlayerSkill::setState, this, _1))) {}
		break;
	case State::None:
		if (handler.tryAppear(shared_from_this())) {}
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
	if (event->key.code == key.playerSkillSwap) {
		if (handler.trySwap()) {
		}
		else {
		}
	}
}

void PlayerSkill::handleSelect(const sf::Event * const event) {
	if (status == Status::None || event->type != sf::Event::MouseButtonPressed 
		|| currentState != GameState::LEVEL_FINISHED) return;
	if (skill.second.context->getGlobalBounds().contains(getTransform().getInverse().transformPoint(
		static_cast<float>(event->mouseButton.x), static_cast<float>(event->mouseButton.y)))) {
		if (uCurrentCarry < uMaxCarry && SkillSystem::selectOn()) {
			++uCurrentCarry;
			return;
		}
		if (SkillSystem::selectOff()) {
			--uCurrentCarry;
			return;
		}
	}
}

void PlayerSkill::loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::pair<State, std::string> &file) {
		statePreviews.emplace(file.first, std::make_shared<sf::Texture>());
		statePreviews.at(file.first)->loadFromFile(file.second);
		statePreviews.at(file.first)->setSmooth(isSmooth);
	});
}

void PlayerSkill::extendCarry(const size_t number) {
	uMaxCarry += number;
}

void PlayerSkill::extendField(const size_t number) {
	if (number + uMaxOnField > static_cast<size_t> (maxField)) {
		throw std::out_of_range("Excess max field number");
	}
	uMaxOnField += number;
}

void PlayerSkill::resetKey(const sf::Keyboard::Key playerSkill, const sf::Keyboard::Key playerSkillSwap
	, const sf::Keyboard::Key switchToPrevChargingSkill, const sf::Keyboard::Key switchToNextChargingSkill) {
	key = { playerSkill, playerSkillSwap, switchToPrevChargingSkill, switchToNextChargingSkill };
}

void PlayerSkill::setState(const State state) {
	if (skill.second.currentState == State::OnCharging) {
		if (uCurrentOnField > uMaxOnField) throw std::invalid_argument("Too many skills on field.");
		++uCurrentOnField;
	}
	else if (state == State::Using) {
		if (uCurrentOnField == 0) throw std::invalid_argument("Field no have any skills.");
		--uCurrentOnField;
	}
	skill.second.currentState = state;
	skill.second.context.reset(new sf::Sprite(*statePreviews.at(state)));
}

void PlayerSkill::swapSkill(const std::shared_ptr<PlayerSkill> & other) {
	State state = skill.second.currentState;
	State inputState = other->skill.second.currentState;
	statePreviews.swap(other->statePreviews);
	skill.swap(other->skill);
	setState(inputState);
	other->setState(state);
}

size_t PlayerSkill::getMaxCarry() {
	return uMaxCarry;
}

size_t PlayerSkill::getCurrentCarry() {
	return uCurrentCarry;
}

size_t PlayerSkill::getMaxOnField() {
	return uMaxOnField;
}

size_t PlayerSkill::getCurrentOnField() {
	return uCurrentOnField;
}

bool PlayerSkill::isInitialize() const {
	return bInitialize;
}

PlayerSkill::State PlayerSkill::getState() const {
	return skill.second.currentState;
}

SkillKind<PlayerSkill>::Kind PlayerSkill::getSkillName() const {
	return skill.first;
}

PlayerSkill::~PlayerSkill() {
}

void PlayerSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (skill.second.currentState == State::None) return;
	states.transform *= getTransform();
	target.draw(*skill.second.context, states);
}

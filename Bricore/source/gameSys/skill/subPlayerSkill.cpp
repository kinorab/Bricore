#include "subPlayerSkill.h"
#include "skillHandler.h"
#include "../effect/entireEffect.h"
#include "../bar/energyBar.h"
#include "../../manager/textureManager.h"
#include "../../definition/gameState.h"
#include "../../event/eventListener.h"
#include <SFML/Graphics.hpp>

using namespace game;

size_t SubPlayerSkill::uMaxCarry(1);
size_t SubPlayerSkill::uCurrentCarry(0);
size_t SubPlayerSkill::uMaxOnField(2);
size_t SubPlayerSkill::uCurrentOnField(0);
SkillHandler<SubPlayerSkill> SubPlayerSkill::handler;
SubPlayerSkill::SkillKey SubPlayerSkill::key;

SubPlayerSkill::SubPlayerSkill(const Kind skillName, const sf::Time duration
	, std::vector<std::pair<Effect::Kind, bool>> && effects, std::vector<Attribute::Kind> && attributes
	, const bool autoUse, const bool exist, const std::shared_ptr<EnergyBar> energyBar)
	: skill(SkillContent{ skillName, State::None, nullptr })
	, SkillSystem(duration, autoUse, exist)
	, m_energyBar(std::move(energyBar))
	, bInitialize(false)
	, bTypeSkill(false) {
	// initialize effects
	std::for_each(effects.begin(), effects.end(), [&](const std::pair<Effect::Kind, bool> & effect) {
		skillEffects.push_back(std::make_shared<EntireEffect>(effect.first, this, effect.second));
	});
	// initialize attributes
	std::for_each(attributes.begin(), attributes.end(), [&](const Attribute::Kind element) {
		skillAttributes.push_back(std::make_shared<Attribute>(element));
	});
}

void SubPlayerSkill::initialize() {
	if (bInitialize) return;
	handler.insert(shared_from_this());
	addListener(std::make_shared<EventListener<KeyPressedEvent>>([this](auto & event) { onKeyPressed(event); }));
	addListener(std::make_shared<EventListener<MousePressedEvent>>([this](auto & event) { onMousePressed(event); }));
	bInitialize = true;
}

void SubPlayerSkill::update() {
	if (status != Status::Selected || currentGameState == GameState::LEVEL_FINISHED) return;
	using namespace std::placeholders;
	State currentState = skill.currentState;
	switch (currentState) {
	case State::OnCharging:
		if (!m_energyBar->isFull() || bLocked) break;
		if (handler.tryEnterField(std::bind(&SubPlayerSkill::setState, this, _1))) {
			m_energyBar->clear();
		}
		break;
	case State::OnSecondField:
		if (bLocked) break;
		handler.tryForward(currentState, std::bind(&SubPlayerSkill::setState, this, _1));
		break;
	case State::OnThirdField:
		if (bLocked) break;
		handler.tryForward(currentState, std::bind(&SubPlayerSkill::setState, this, _1));
		break;
	case State::None:
		handler.tryAppear(shared_from_this());
		break;
	case State::Using:
		SkillSystem::useSkill();
		if (SkillSystem::elapsed()) {
			SkillSystem::exhausted();
			setState(State::None);
		}
		break;
	default:
		break;
	}
}

bool SubPlayerSkill::containsPoint(const sf::Vector2f & point) const {
	if (skill.currentState == State::None) return false;
	return skill.context->getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> SubPlayerSkill::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void SubPlayerSkill::loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::pair<State, std::string> & file) {
		statePreviews.emplace(file.first, TextureManager::getInstance().get(file.second));
		statePreviews[file.first]->setSmooth(isSmooth);
	});
}

void SubPlayerSkill::extendCarry(const size_t number) {
	uMaxCarry += number;
}

void SubPlayerSkill::extendField(const size_t number) {
	if (number + uMaxOnField > static_cast<size_t> (maxField)) {
		throw std::out_of_range("Excess max field number");
	}
	uMaxOnField += number;
}

void SubPlayerSkill::resetKey(const sf::Keyboard::Key subSkill, const sf::Keyboard::Key subSkillSwap
	, const sf::Keyboard::Key turnSkillToTypeSkill, const sf::Keyboard::Key switchToPrevChargingSkill
	, const sf::Keyboard::Key switchToNextChargingSkill) {
	key = { subSkill, subSkillSwap, turnSkillToTypeSkill, switchToPrevChargingSkill, switchToNextChargingSkill };
}

void SubPlayerSkill::setState(const State nextState) {
	// set field number
	if (skill.currentState == State::OnCharging) {
		if (uCurrentOnField > uMaxOnField) throw std::invalid_argument("Too many skills on field.");
		++uCurrentOnField;
	}
	else if (nextState == State::Using) {
		if (uCurrentOnField == 0) throw std::invalid_argument("Field not have any skills.");
		--uCurrentOnField;
	}
	// set skill context
	if (nextState == State::None) {
		skill.context = nullptr;
	}
	else {
		skill.context.reset(new sf::Sprite(*statePreviews[nextState]));
	}
	// set skill state
	skill.currentState = nextState;
}

void SubPlayerSkill::swapSkill(const std::shared_ptr<SubPlayerSkill> & other) {
	State state = skill.currentState;
	State inputState = other->skill.currentState;
	statePreviews.swap(other->statePreviews);
	std::swap(skill, other->skill);
	setState(inputState);
	other->setState(state);
}

size_t SubPlayerSkill::getMaxCarry() {
	return uMaxCarry;
}

size_t SubPlayerSkill::getCurrentCarry() {
	return uCurrentCarry;
}

size_t SubPlayerSkill::getMaxOnField() {
	return uMaxOnField;
}

size_t SubPlayerSkill::getCurrentOnField() {
	return uCurrentOnField;
}

bool SubPlayerSkill::isInitialize() const {
	return bInitialize;
}

SubPlayerSkill::State SubPlayerSkill::getState() const {
	return skill.currentState;
}

SkillKind<SubPlayerSkill>::Kind SubPlayerSkill::getSkillName() const {
	return skill.name;
}

SubPlayerSkill::~SubPlayerSkill() {
}

void SubPlayerSkill::onKeyPressed(KeyPressedEvent & event) {
	if (skill.currentState == State::OnFirstField) {
		if (bSilenced) return;
		if (event.pressed.code == key.turnSkillToTypeSkill) {
			bTypeSkill = true;
		}
		if (event.pressed.code == key.subSkill || bAutoUse) setState(State::Using);
	}
	if (event.pressed.code != key.subSkillSwap) return;
	if (handler.trySwap()) {

	}
	else {

	}
}

void SubPlayerSkill::onMousePressed(MousePressedEvent & event) {
	if (currentGameState != GameState::LEVEL_FINISHED
		|| containsPoint(sf::Vector2f(static_cast<float>(event.pressed.x)
			, static_cast<float>(event.pressed.y)))) return;
	// left mouse to choose
	if (uCurrentCarry < uMaxCarry && SkillSystem::selectOn() && event.pressed.button == sf::Mouse::Left) {
		++uCurrentCarry;
		return;
	}
	// left or right mouse to cancel choose
	if (SkillSystem::selectOff() && 
		(event.pressed.button == sf::Mouse::Left || event.pressed.button == sf::Mouse::Right)) {
		--uCurrentCarry;
		return;
	}
}

void SubPlayerSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (skill.currentState == State::None) return;
	target.draw(*skill.context, states);
}

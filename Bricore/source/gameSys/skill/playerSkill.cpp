#include "playerSkill.h"
#include "skillHandler.h"
#include "../effect/entireEffect.h"
#include "../bar/energyBar.h"
#include "../../manager/textureManager.h"
#include "../../definition/gameState.h"
#include "../../event/eventListener.h"
#include <SFML/Graphics.hpp>

using namespace game;

size_t PlayerSkill::uMaxCarry(3);
size_t PlayerSkill::uCurrentCarry(0);
size_t PlayerSkill::uMaxOnField(2);
size_t PlayerSkill::uCurrentOnField(0);
SkillHandler<PlayerSkill> PlayerSkill::handler;
PlayerSkill::SkillKey PlayerSkill::key;

PlayerSkill::PlayerSkill(const Kind skillName, const sf::Time duration
	, std::vector<std::pair<Effect::Kind, bool>> && effects, std::vector<Attribute::Kind> && attributes
	, const bool autoUse, const bool exist, const std::shared_ptr<EnergyBar> energyBar)
	: skill(SkillContent{ skillName, State::Waiting, nullptr })
	, SkillSystem(duration, autoUse, exist)
	, m_energyBar(std::move(energyBar))
	, bInitialize(false) {
	// initialize effects
	std::for_each(effects.begin(), effects.end(), [&](const std::pair<Effect::Kind, bool> & effect) {
		skillEffects.push_back(std::make_shared<EntireEffect>(effect.first, this, effect.second));
	});
	// initialize attributes
	std::for_each(attributes.begin(), attributes.end(), [&](const Attribute::Kind element) {
		skillAttributes.push_back(std::make_shared<Attribute>(element));
	});
}

void PlayerSkill::initialize() {
	if (bInitialize) return;
	handler.insert(shared_from_this());
	addListener(std::make_shared<EventListener<KeyPressedEvent>>([this](auto & event) { onKeyPressed(event); }));
	addListener(std::make_shared<EventListener<MousePressedEvent>>([this](auto & event) { onMousePressed(event); }));
	addListener(std::make_shared<EventListener<GameFinishedLevelEvent>>([this](auto & event) { onGameFinishedLevel(event); }));
	bInitialize = true;
}

void PlayerSkill::update() {
	State currentState = skill.currentState;
	if (status != Status::Selected) return;
	using namespace std::placeholders;
	switch (currentState) {
	case State::OnCharging:
		if (!m_energyBar->isFull() || bLocked) break;
		if (handler.tryEnterField(std::bind(&PlayerSkill::setState, this, _1))) {
			m_energyBar->clear();
		}
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
	case State::Waiting:
		if (handler.tryAppear(shared_from_this())) {}
		break;
	case State::Using:
		useSkill();
		if (elapsed()) {
			exhausted();
			setState(State::Waiting);
		}
		break;
	default:
		break;
	}
}

bool PlayerSkill::containsPoint(const sf::Vector2f & point) const {
	if (skill.currentState == State::Waiting) return false;
	return skill.context->getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> PlayerSkill::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void PlayerSkill::loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::pair<State, std::string> & file) {
		statePreviews.emplace(file.first, TextureManager::getInstance().get(file.second));
		statePreviews[file.first]->setSmooth(isSmooth);
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

void PlayerSkill::setState(const State nextState) {
	// skip if same
	if (skill.currentState == nextState) return;
	// set field number
	if (skill.currentState == State::OnCharging) {
		if (uCurrentOnField > uMaxOnField) throw std::invalid_argument("Too many skills on field.");
		++uCurrentOnField;
	}
	else if (nextState == State::Using) {
		if (uCurrentOnField == 0) throw std::invalid_argument("Field no have any skills.");
		--uCurrentOnField;
	}
	// set skill context
	if (nextState == State::Waiting) {
		skill.context = nullptr;
	}
	else {
		skill.context.reset(new sf::Sprite(*statePreviews[nextState]));
	}
	// set skill state
	skill.currentState = nextState;
}

void PlayerSkill::swapSkill(const std::shared_ptr<PlayerSkill> & other) {
	State state = skill.currentState;
	State inputState = other->skill.currentState;
	statePreviews.swap(other->statePreviews);
	std::swap(skill, other->skill);
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
	return skill.currentState;
}

SkillKind<PlayerSkill>::Kind PlayerSkill::getSkillName() const {
	return skill.name;
}

PlayerSkill::~PlayerSkill() {
}

void PlayerSkill::onKeyPressed(KeyPressedEvent & event) {
	if (skill.currentState == State::Display) return;
	if (skill.currentState == State::OnFirstField) {
		if (bSilenced) return;
		if (event.pressed.code == key.playerSkill || bAutoUse) setState(State::Using);
	}
	if (event.pressed.code != key.playerSkillSwap) return;
	if (handler.trySwap()) {

	}
	else {

	}
}

void PlayerSkill::onMousePressed(MousePressedEvent & event) {
	if (skill.currentState == State::Display || containsPoint(sf::Vector2f(static_cast<float>(event.pressed.x)
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

void PlayerSkill::onGameFinishedLevel(GameFinishedLevelEvent & event) {
	setState(State::Display);
}

void PlayerSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (skill.currentState == State::Waiting) return;
	target.draw(*skill.context, states);
}

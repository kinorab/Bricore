#include "playerSkill.h"
#include "skillHandler.h"
#include "../bar/energyBar.h"
#include "../../manager/textureManager.h"
#include "../../definition/gameState.h"
#include "../../event/eventListener.h"
#include "../../stuff/player.h"
#include <SFML/Graphics.hpp>

using namespace game;

size_t PlayerSkill::uMaxCarry(3);
size_t PlayerSkill::uCurrentCarry(0);
size_t PlayerSkill::uMaxOnField(2);
size_t PlayerSkill::uCurrentOnField(0);
SkillHandler<PlayerSkill> PlayerSkill::handler;
std::map<PlayerSkill::Kind, std::map<PlayerSkill::State, std::string>> PlayerSkill::fileNames({
	std::pair(AmbitGuard
	, std::map<PlayerSkill::State, std::string>{
		std::pair(State::OnCharging, "defenderSkill/ambitGuard_onCharging")
		, std::pair(State::OnFirstField, "defenderSkill/ambitGuard_onFirstField")
		, std::pair(State::OnSecondField, "defenderSkill/ambitGuard_onSecondField")
		, std::pair(State::OnThirdField, "defenderSkill/ambitGuard_onThirdField")
		, std::pair(State::OnFourthField, "defenderSkill/ambitGuard_onFourthField")
		, std::pair(State::Using, "defenderSkill/ambitGuard_using")
		, std::pair(State::Display, "defenderSkill/ambitGuard_display")
		, std::pair(State::Prepare, "defenderSkill/ambitGuard_prepare")
		})
	});

PlayerSkill::PlayerSkill(const Kind skillName, const sf::Time duration
	, std::vector<std::pair<Effect::Kind, bool>> && effects, std::vector<Attribute::Kind> && attributes
	, const bool exist, const std::shared_ptr<EnergyBar> energyBar, const Player * player)
	: skill(SkillContent{ skillName, State::Waiting, nullptr })
	, SkillSystem(duration, exist)
	, bInitialize(false)
	, m_energyBar(std::move(energyBar))
	, c_player(player) {
	// initialize effects
	std::for_each(effects.begin(), effects.end(), [&](const std::pair<Effect::Kind, bool> & effect) {
		skillEffects.push_back(std::make_shared<Effect>(effect.first, effect.second));
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
	addListener(std::make_shared<EventListener<GameStartedEvent>>([this](auto & event) { onGameStarted(event); }));
	addListener(std::make_shared<EventListener<GameReadyEvent>>([this](auto & event) { onGameReady(event); }));
	addListener(std::make_shared<EventListener<GameFinishedLevelEvent>>([this](auto & event) { onGameFinishedLevel(event); }));
	addListener(std::make_shared<EventListener<GamePreparedEvent>>([this](auto & event) { onGamePrepared(event); }));
	bInitialize = true;
}

void PlayerSkill::update() {
	if (status != Status::Selected) return;
	using namespace std::placeholders;
	State currentState = skill.currentState;
	switch (currentState) {
	case State::OnCharging:
		if (!m_energyBar->isFull() || bLocked) break;
		if (handler.tryEnterField(std::bind(&PlayerSkill::setState, this, _1))) {
			m_energyBar->clear();
		}
		break;
	case State::OnSecondField:
		if (bLocked) break;
		handler.tryForward(currentState, std::bind(&PlayerSkill::setState, this, _1));
		break;
	case State::OnThirdField:
		if (bLocked) break;
		handler.tryForward(currentState, std::bind(&PlayerSkill::setState, this, _1));
		break;
	case State::OnFourthField:
		if (bLocked) break;
		handler.tryForward(currentState, std::bind(&PlayerSkill::setState, this, _1));
		break;
	case State::Waiting:
		handler.tryAppear(shared_from_this());
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
	return getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> PlayerSkill::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void PlayerSkill::setPosition(const sf::Vector2f & position) {
	skill.context->setPosition(position);
}

void PlayerSkill::setPosition(const float x, const float y) {
	skill.context->setPosition(x, y);
}

void PlayerSkill::setOrigin(const sf::Vector2f & origin) {
	this->origin = origin;
}

void PlayerSkill::setOrigin(const float x, const float y) {
	origin = { x, y };
}

void PlayerSkill::setOwnToPlayer(const bool giveOwn) {
	if (!isExist()) throw std::invalid_argument("Skill not exist in setOwn.");
	if (giveOwn) {
		status = UnSelected;
	}
	else {
		status = None;
	}
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
		auto stateTexture = TextureManager::getInstance().get(fileNames[skill.name][skill.currentState]);
		skill.context.reset(new sf::Sprite(*stateTexture));
		skill.context->setOrigin(origin);
		// show gray filter if player no own this skill
		if (nextState == State::Display && status == Status::None) {
			skill.context->setColor(sf::Color(150, 150, 150, 180));
		}
		else {
			skill.context->setColor(sf::Color::White);
		}
	}
	// set skill state
	skill.currentState = nextState;
}

void PlayerSkill::swapSkill(const std::shared_ptr<PlayerSkill> & other) {
	State state = skill.currentState;
	State inputState = other->skill.currentState;
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

bool PlayerSkill::isOwnToPlayer() const {
	if (status == Status::None) return false;
	return true;
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

sf::FloatRect PlayerSkill::getLocalBounds() const {
	return skill.context->getLocalBounds();
}

sf::FloatRect PlayerSkill::getGlobalBounds() const {
	return skill.context->getGlobalBounds();
}

PlayerSkill::~PlayerSkill() {
}

void PlayerSkill::onKeyPressed(KeyPressedEvent & event) {
	if (skill.currentState == State::Display || skill.currentState == State::Prepare) return;
	if (skill.currentState == State::OnFirstField) {
		if (bSilenced) return;
		if (event.pressed.code == c_player->getKey().playerSkill || c_player->isAutoUse(Player::SkillSelect::_Player)) {
			setState(State::Using);
		}
	}
	if (event.pressed.code != c_player->getKey().playerSkillSwap) return;
	if (handler.trySwap()) {

	}
	else {

	}
}

void PlayerSkill::onMousePressed(MousePressedEvent & event) {
	if (skill.currentState != State::Prepare) return;
	// left mouse to choose
	if (uCurrentCarry < uMaxCarry && SkillSystem::selectOn() && event.pressed.button == sf::Mouse::Left) {
		skill.context->setColor(sf::Color::White);
		++uCurrentCarry;
		return;
	}
	// left or right mouse to cancel choose
	if (SkillSystem::selectOff() &&
		(event.pressed.button == sf::Mouse::Left || event.pressed.button == sf::Mouse::Right)) {
		// show gray filter if skill no choose
		skill.context->setColor(sf::Color(180, 180, 180));
		--uCurrentCarry;
		return;
	}
}

void PlayerSkill::onGameStarted(GameStartedEvent & event) {
	update();
}

void PlayerSkill::onGameReady(GameReadyEvent & event) {
	setState(State::Waiting);
}

void PlayerSkill::onGameFinishedLevel(GameFinishedLevelEvent & event) {
	setState(State::Display);
}

void PlayerSkill::onGamePrepared(GamePreparedEvent & event) {
	setState(State::Prepare);
}

void PlayerSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (skill.currentState == State::Waiting) return;
	target.draw(*skill.context, states);
}

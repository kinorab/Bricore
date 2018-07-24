#include "ballSkill.h"
#include "skillHandler.h"
#include "../../manager/textureManager.h"
#include "../../definition/gameState.h"
#include "../../event/eventListener.h"
#include "../../stuff/player.h"
#include <SFML/Graphics.hpp>

using namespace game;

size_t BallSkill::uMaxDropping(5);
size_t BallSkill::uCurrentCarry(0);
size_t BallSkill::uMaxOnField(2);
size_t BallSkill::uCurrentOnField(0);
std::map<int, std::string> BallSkill::frameFileNames({
	std::pair(1, "frame/frame_1")
	, std::pair(2, "frame/frame_2")
	, std::pair(3, "frame/frame_3")
	, std::pair(4, "frame/frame_4")
	, std::pair(5, "frame/frame_5")
	, std::pair(6, "frame/frame_6")
	, std::pair(7, "frame/frame_7")
	, std::pair(8, "frame/frame_8")
	, std::pair(9, "frame/frame_9")
	, std::pair(10, "frame/frame_10")
	});
std::map<BallSkill::Kind, std::map<BallSkill::State, std::string>> BallSkill::fileNames({
	std::pair(HugeBody,
		std::map<BallSkill::State, std::string>{
		std::pair(State::OnDropping, "ballSkill/hugeBody_onDropping")
		, std::pair(State::OnFirstField, "ballSkill/hugeBody_onFirstField")
		, std::pair(State::OnSecondField, "ballSkill/hugeBody_onSecondField")
		, std::pair(State::OnThirdField, "ballSkill/hugeBody_onThirdField")
		, std::pair(State::OnFourthField, "ballSkill/hugeBody_onFourthField")
		, std::pair(State::Using, "ballSkill/hugeBody_using")
		, std::pair(State::Display, "ballSkill/hugeBody_display")
		, std::pair(State::Prepare, "ballSkill/hugeBody_prepare")
		})
	, std::pair(MultipleAttack,
		std::map<BallSkill::State, std::string>{
			std::pair(State::OnDropping, "ballSkill/multipleAttack_onDropping")
			, std::pair(State::OnFirstField, "ballSkill/multipleAttack_onFirstField")
			, std::pair(State::OnSecondField, "ballSkill/multipleAttack_onSecondField")
			, std::pair(State::OnThirdField, "ballSkill/multipleAttack_onThirdField")
			, std::pair(State::OnFourthField, "ballSkill/multipleAttack_onFourthField")
			, std::pair(State::Using, "ballSkill/multipleAttack_using")
			, std::pair(State::Display, "ballSkill/multipleAttack_display")
			, std::pair(State::Prepare, "ballSkill/multipleAttack_prepare")
		})
	});
SkillHandler<BallSkill> BallSkill::handler;

BallSkill::BallSkill(const Kind skillName, const sf::Time duration
	, std::vector<std::pair<Effect::Kind, bool>> && effects, std::vector<Attribute::Kind> && attributes
	, const bool exist, const Player * player)
	: SkillSystem(duration, exist)
	, bInitialize(false)
	, origin()
	, skill(SkillContent{ skillName, State::Waiting, nullptr, nullptr })
	, c_player(player) {
	// initialize effects
	std::for_each(effects.begin(), effects.end(), [&](const std::pair<Effect::Kind, bool> & effect) {
		skillEffects.push_back(std::make_shared<Effect>(effect.first, effect.second));
	});
	// initialize attribute
	std::for_each(attributes.begin(), attributes.end(), [&](const Attribute::Kind element) {
		skillAttributes.push_back(std::make_shared<Attribute>(element));
	});
}

void BallSkill::initialize() {
	if (bInitialize) return;
	handler.insert(shared_from_this());
	addListener(std::make_shared<EventListener<KeyPressedEvent>>([this](auto & event) { onKeyPressed(event); }));
	addListener(std::make_shared<EventListener<MousePressedEvent>>([this](auto & event) { onMousePressed(event); }));
	addListener(std::make_shared<EventListener<GameStartedEvent>>([this](auto & event) { onGameStarted(event); }));
	addListener(std::make_shared<EventListener<GameReadyEvent>>([this](auto & event) { onGameReady(event); }));
	addListener(std::make_shared<EventListener<GameFinishedLevelEvent>>([this](auto & event) { onGameFinishedLevel(event); }));
	bInitialize = true;
}

void BallSkill::update() {
	if (status != Status::Selected) return;
	using namespace std::placeholders;
	State currentState = skill.currentState;
	switch (currentState) {
	case State::OnDropping:
		handler.tryEnterField(std::bind(&BallSkill::setState, this, _1));
		break;
	case State::OnSecondField:
		if (bLocked) break;
		handler.tryForward(currentState, std::bind(&BallSkill::setState, this, _1));
		break;
	case State::OnThirdField:
		if (bLocked) break;
		handler.tryForward(currentState, std::bind(&BallSkill::setState, this, _1));
		break;
	case State::OnFourthField:
		if (bLocked) break;
		handler.tryForward(currentState, std::bind(&BallSkill::setState, this, _1));
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

bool BallSkill::containsPoint(const sf::Vector2f & point) const {
	if (skill.currentState == State::Waiting) return false;
	return getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> BallSkill::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void BallSkill::setPosition(const sf::Vector2f & position) {
	if (skill.frame) {
		skill.frame->setPosition(position);
		// offset 10 right and bottom(frame size 10)
		skill.context->setPosition(position.x + 10.f, position.y + 10.f);
	}
	else {
		skill.context->setPosition(position);
	}
}

void BallSkill::setPosition(const float x, const float y) {
	if (skill.frame) {
		skill.frame->setPosition(x, y);
		// offset 10 right and bottom(frame size 10)
		skill.context->setPosition(x + 10.f, y + 10.f);
	}
	else {
		skill.context->setPosition(x, y);
	}
}

void BallSkill::setOrigin(const sf::Vector2f & origin) {
	this->origin = origin;
}

void BallSkill::setOrigin(const float x, const float y) {
	origin = { x, y };
}

void BallSkill::setOwnToPlayer(const bool giveOwn) {
	if (!isExist()) throw std::invalid_argument("Skill not exist in setOwn.");
	if (giveOwn) {
		status = UnSelected;
	}
	else {
		status = None;
	}
}

void BallSkill::setState(const State nextState) {
	// skip if same
	if (skill.currentState == nextState) return;
	// set field number
	if (skill.currentState == State::OnDropping) {
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
		// align to frame white space
		skill.context->setPosition(skill.frame->getPosition().x + 10.f, skill.frame->getPosition().y + 10.f);
		// show gray filter if player no own this skill
		if (nextState == State::Display && status == Status::None) {
			skill.context->setColor(sf::Color(150, 150, 150, 180));
		}
		else {
			skill.context->setColor(sf::Color::White);
		}
	}
	// set frame context
	if (nextState == State::OnDropping) {
		auto frameTexture = TextureManager::getInstance().get(frameFileNames[uLevel]);
		skill.frame.reset(new sf::Sprite(*frameTexture));
		skill.frame->setOrigin(origin);
	}
	else if (skill.frame) {
		skill.frame = nullptr;
	}
	// set skill state
	skill.currentState = nextState;
}

void BallSkill::swapSkill(const std::shared_ptr<BallSkill> & other) {
	State state = skill.currentState;
	State inputState = other->skill.currentState;
	std::swap(skill, other->skill);
	setState(inputState);
	other->setState(state);
}

void BallSkill::extendField(size_t number) {
	if (number + uMaxOnField > static_cast<size_t> (maxField)) {
		throw std::out_of_range("Excess max field number");
	}
	uMaxOnField += number;
}

void BallSkill::extendDropping(size_t number) {
	uMaxDropping += number;
}

size_t BallSkill::getMaxDropping() {
	return uMaxDropping;
}

size_t BallSkill::getCurrentCarry() {
	return uCurrentCarry;
}

size_t BallSkill::getMaxOnField() {
	return uMaxOnField;
}

size_t BallSkill::getCurrentOnField() {
	return uCurrentOnField;
}

bool BallSkill::isOwnToPlayer() const {
	if (status == Status::None) return false;
	return true;
}

bool BallSkill::isInitialize() const {
	return bInitialize;
}

BallSkill::State BallSkill::getState() const {
	return skill.currentState;
}

SkillKind<BallSkill>::Kind BallSkill::getSkillName() const {
	return skill.name;
}

const sf::Vector2f & BallSkill::getPosition() const {
	if (skill.frame) {
		return skill.frame->getPosition();
	}
	return skill.context->getPosition();
}

sf::FloatRect BallSkill::getLocalBounds() const {
	if (skill.frame) {
		return skill.frame->getLocalBounds();
	}
	return skill.context->getLocalBounds();
}

sf::FloatRect BallSkill::getGlobalBounds() const {
	if (skill.frame) {
		return skill.frame->getGlobalBounds();
	}
	return skill.context->getGlobalBounds();
}

BallSkill::~BallSkill() {
}

void BallSkill::onKeyPressed(KeyPressedEvent & event) {
	if (skill.currentState == State::Display || skill.currentState == State::Prepare) return;
	if (skill.currentState == State::OnFirstField) {
		if (bSilenced) return;
		if (event.pressed.code == c_player->getKey().ballSkill || c_player->isAutoUse(Player::SkillSelect::_Ball)) {
			setState(State::Using);
		}
	}
	if (event.pressed.code != c_player->getKey().ballSkillSwap) return;
	if (handler.trySwap()) {

	}
	else {

	}
}

void BallSkill::onMousePressed(MousePressedEvent & event) {
	if (skill.currentState != State::Prepare) return;
	// left mouse to choose
	if (SkillSystem::selectOn() && event.pressed.button == sf::Mouse::Left) {
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

void BallSkill::onGameStarted(GameStartedEvent & event) {
	update();
}

void BallSkill::onGameReady(GameReadyEvent & event) {
	setState(State::Waiting);
}

void BallSkill::onGameFinishedLevel(GameFinishedLevelEvent & event) {
	setState(State::Display);
}

void BallSkill::onGamePrepared(GamePreparedEvent & event) {
	setState(State::Prepare);
}

void BallSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (skill.currentState == State::Waiting) return;
	if (skill.frame) {
		target.draw(*skill.frame, states);
	}
	target.draw(*skill.context, states);
}

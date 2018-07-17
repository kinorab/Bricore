#include "ballSkill.h"
#include "skillHandler.h"
#include "../effect/entireEffect.h"
#include "../../manager/textureManager.h"
#include "../../definition/gameState.h"
#include "../../event/eventListener.h"
#include <SFML/Graphics.hpp>

using namespace game;

size_t BallSkill::uMaxDropping(5);
size_t BallSkill::uCurrentCarry(0);
size_t BallSkill::uMaxOnField(2);
size_t BallSkill::uCurrentOnField(0);
std::map<std::string, std::shared_ptr<sf::Texture>> BallSkill::framePreviews;
SkillHandler<BallSkill> BallSkill::handler;
BallSkill::SkillKey BallSkill::key;

BallSkill::BallSkill(const Kind skillName, const sf::Time duration
	, std::vector<std::pair<Effect::Kind, bool>> && effects, std::vector<Attribute::Kind> && attributes
	, const bool autoUse, const bool exist)
	: SkillSystem(duration, autoUse, exist)
	, skill(SkillContent{ skillName, State::Waiting, nullptr, nullptr })
	, bInitialize(false) {
	// initialize effects
	std::for_each(effects.begin(), effects.end(), [&](const std::pair<Effect::Kind, bool> & effect) {
		skillEffects.push_back(std::make_shared<EntireEffect>(effect.first, this, effect.second));
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
	addListener(std::make_shared<EventListener<GameFinishedLevelEvent>>([this](auto & event) { onGameFinishedLevel(event); }));
	bInitialize = true;
}

void BallSkill::update() {
	if (status != Status::Selected) return;
	using namespace std::placeholders;
	State currentState = skill.currentState;
	switch (currentState) {
	case State::OnDropping:
		if (handler.tryEnterField(std::bind(&BallSkill::setState, this, _1))) {

		}
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
	case State::Display:
		break;
	default:
		break;
	}
}

void BallSkill::loadFrame(const std::vector<std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::string &file) {
		framePreviews.emplace(file, TextureManager::getInstance().get(file));
		framePreviews[file]->setSmooth(isSmooth);
	});
}

bool BallSkill::containsPoint(const sf::Vector2f & point) const {
	if (skill.currentState == State::Waiting) return false;
	if (skill.frame) {
		return skill.frame->getGlobalBounds().contains(point);
	}
	return skill.context->getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> BallSkill::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void BallSkill::loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::pair<State, std::string> & file) {
		statePreviews.emplace(file.first, TextureManager::getInstance().get(file.second));
		statePreviews[file.first]->setSmooth(isSmooth);
	});
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
		skill.context.reset(new sf::Sprite(*statePreviews[nextState]));
		skill.context->setOrigin(skill.context->getLocalBounds().width / 2.f
			, skill.context->getLocalBounds().height / 2.f);
		skill.context->setPosition(skill.frame->getPosition());
	}
	// set frame context
	if (nextState == State::OnDropping) {
		for (auto iter = framePreviews.begin(); iter != framePreviews.end(); ++iter) {
			if (iter->first.find(std::to_string(uLevel)) != std::string::npos) {
				skill.frame.reset(new sf::Sprite(*framePreviews[iter->first]));
				skill.frame->setOrigin(skill.frame->getLocalBounds().width / 2.f
					, skill.frame->getLocalBounds().height / 2.f);
				break;
			}
		}

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
	statePreviews.swap(other->statePreviews);
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

void BallSkill::resetKey(const sf::Keyboard::Key ballSkill, const sf::Keyboard::Key ballSkillSwap) {
	key = { ballSkill, ballSkillSwap };
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

bool BallSkill::isInitialize() const {
	return bInitialize;
}

BallSkill::State BallSkill::getState() const {
	return skill.currentState;
}

SkillKind<BallSkill>::Kind BallSkill::getSkillName() const {
	return skill.name;
}

BallSkill::~BallSkill() {
}

void BallSkill::onKeyPressed(KeyPressedEvent & event) {
	if (skill.currentState == State::Display) return;
	if (skill.currentState == State::OnFirstField) {
		if (bSilenced) return;
		if (event.pressed.code == key.ballSkill || bAutoUse) setState(State::Using);
	}
	if (event.pressed.code != key.ballSkillSwap) return;
	if (handler.trySwap()) {

	}
	else {

	}
}

void BallSkill::onMousePressed(MousePressedEvent & event) {
	if (skill.currentState == State::Display || containsPoint(sf::Vector2f(static_cast<float>(event.pressed.x)
		, static_cast<float>(event.pressed.y)))) return;
	// left mouse to choose
	if (SkillSystem::selectOn() && event.pressed.button == sf::Mouse::Left) {
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

void BallSkill::onGameFinishedLevel(GameFinishedLevelEvent & event) {
	setState(State::Display);
}

void BallSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (skill.currentState == State::Waiting) return;
	target.draw(*skill.context, states);
	if (skill.frame) {
		target.draw(*skill.frame, states);
	}
}

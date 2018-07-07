#include "ballSkill.h"
#include "skillHandler.h"
#include "../effect/entireEffect.h"
#include "../../definition/gameState.h"
#include <SFML/Graphics.hpp>

using namespace game;

size_t BallSkill::uMaxDropping(5);
size_t BallSkill::uCurrentCarry(0);
size_t BallSkill::uMaxOnField(2);
size_t BallSkill::uCurrentOnField(0);
std::map<std::string, std::shared_ptr<sf::Texture>> BallSkill::framePreviews;
SkillHandler<BallSkill> BallSkill::handler(sf::Keyboard::D, sf::Keyboard::E);

BallSkill::BallSkill(const Kind skillName, const sf::Time duration
	, const std::vector<Effect::Kind> &effects
	, const std::vector<Attribute::Kind> &attributes, const bool autoUse)
	: skill(skillName, SkillContent{ State::None, nullptr, nullptr })
	, SkillSystem(duration, autoUse) {
	std::for_each(effects.begin(), effects.end(), [&](const Effect::Kind effect) {
		skillEffects.push_back(std::make_shared<EntireEffect>(effect, this));
	});
	std::for_each(attributes.begin(), attributes.end(), [&](const Attribute::Kind element) {
		skillAttributes.push_back(std::make_shared<Attribute>(element));
	});
	handler.insert(shared_from_this());
}

void BallSkill::loadFrame(const std::vector<std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::string &file) {
		framePreviews.emplace(file, std::make_shared<sf::Texture>());
		framePreviews.at(file)->loadFromFile(file);
		framePreviews.at(file)->setSmooth(isSmooth);
	});
}

void BallSkill::handleSkill(const sf::Event * const event) {
	if (status != Status::Selected || game::currentState == GameState::LEVEL_FINISHED) return;
	using namespace std::placeholders;
	State currentState = skill.second.currentState;
	switch (currentState) {
	case State::OnDropping:
		if (handler.tryEnterField(std::bind(&BallSkill::setState, this, _1))) {

		}
		break;
	case State::OnFirstField:
		if (bSilenced) break;
		if (event->key.code == handler.useKey || bAutoUse) setState(State::Using);
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

void BallSkill::handleSelect(const sf::Event * const event) {
	if (status == Status::None || event->type != sf::Event::MouseButtonPressed
		|| game::currentState != GameState::LEVEL_FINISHED) return;
	if (skill.second.context->getGlobalBounds().contains(getTransform().getInverse().transformPoint(
		static_cast<float>(event->mouseButton.x), static_cast<float>(event->mouseButton.y)))) {
		if (selectOn()) {
			++uCurrentCarry;
			return;
		}
		if (selectOff()) {
			--uCurrentCarry;
			return;
		}
	}
}

void BallSkill::loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::pair<State, std::string> &file) {
		statePreviews.emplace(file.first, std::make_shared<sf::Texture>());
		statePreviews.at(file.first)->loadFromFile(file.second);
		statePreviews.at(file.first)->setSmooth(isSmooth);
	});
}

void BallSkill::setState(const State state) {
	if (skill.second.currentState == State::OnDropping) {
		if (uCurrentOnField > uMaxOnField) throw std::invalid_argument("Too many skills on field.");
		++uCurrentOnField;
	}
	else if (state == State::Using) {
		if (uCurrentOnField == 0) throw std::invalid_argument("Field no have any skills.");
		--uCurrentOnField;
	}
	skill.second.currentState = state;
	skill.second.context.reset(new sf::Sprite(*statePreviews.at(state)));
	auto context = skill.second.context;
	auto frame = skill.second.frame;
	skill.second.currentState = state;
	context.reset(new sf::Sprite(*statePreviews.at(state)));
	if (state == State::OnDropping) {
		for (auto iter = framePreviews.begin(); iter != framePreviews.end(); ++iter) {
			if (iter->first.find(std::to_string(uLevel)) != std::string::npos) {
				frame.reset(new sf::Sprite(*framePreviews.at(iter->first)));
				frame->setOrigin(frame->getTextureRect().width / 2.f, frame->getTextureRect().height / 2.f);
				break;
			}
		}
		context->setOrigin(context->getTextureRect().width / 2.f, context->getTextureRect().height / 2.f);
		context->setPosition(frame->getPosition());
	}
	else if (frame) {
		frame = nullptr;
	}
}

void BallSkill::swapSkill(const std::shared_ptr<BallSkill> other) {
	State state = skill.second.currentState;
	State inputState = other->skill.second.currentState;
	statePreviews.swap(other->statePreviews);
	skill.swap(other->skill);
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

void BallSkill::resetKey(const sf::Keyboard::Key useKey, const sf::Keyboard::Key swapKey) {
	handler.useKey = useKey;
	handler.swapKey = swapKey;
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

BallSkill::State BallSkill::getState() const {
	return skill.second.currentState;
}

SkillKind<BallSkill>::Kind BallSkill::getSkillName() const {
	return skill.first;
}

BallSkill::~BallSkill() {
}

void BallSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (skill.second.currentState == State::None) return;
	states.transform *= getTransform();
	target.draw(*skill.second.context, states);
	if (skill.second.frame) {
		target.draw(*skill.second.frame, states);
	}
}

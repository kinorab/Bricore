#include "bossSkill.h"
#include "skillHandler.h"
#include "../effect/entireEffect.h"
#include "../bar/rageBar.h"
#include "../../manager/textureManager.h"
#include "../../definition/gameState.h"
#include <SFML/Graphics.hpp>

using namespace game;

SkillHandler<BossSkill> BossSkill::handler;

BossSkill::BossSkill(const Kind skillName, const sf::Time &duration
	, std::vector<std::pair<Effect::Kind, bool>> && effects, std::vector<Attribute::Kind> && attributes
	, const bool exist, const std::shared_ptr<RageBar> rageBar)
	: SkillSystem(duration, true, exist)
	, skill(SkillContent{ skillName, State::None, nullptr })
	, m_rageBar(std::move(rageBar))
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

void BossSkill::initialize() {
	if (bInitialize) return;
	handler.insert(shared_from_this());
	bInitialize = true;
}

void BossSkill::update() {
}

bool BossSkill::containsPoint(const sf::Vector2f & point) const {
	if (skill.currentState == State::None) return false;
	return skill.preview->getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> BossSkill::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
}

void BossSkill::loadStatePreview(const std::map<State, std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::pair<State, std::string> & file) {
		statePreviews.emplace(file.first, TextureManager::getInstance().get(file.second));
		statePreviews[file.first]->setSmooth(isSmooth);
	});
}

bool BossSkill::isInitialize() const {
	return bInitialize;
}

SkillState<BossSkill>::State BossSkill::getState() const {
	return skill.currentState;
}

SkillKind<BossSkill>::Kind BossSkill::getSkillName() const {
	return skill.name;
}

BossSkill::~BossSkill() {
}

void BossSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (skill.currentState == State::None) return;
	target.draw(*skill.preview, states);
}

void BossSkill::setState(const State nextState) {
	// set skill preview
	if (nextState == State::None) {
		skill.preview = nullptr;
	}
	else {
		skill.preview.reset(new sf::Sprite(*statePreviews[nextState]));
	}
	// set skill state
	skill.currentState = nextState;
}

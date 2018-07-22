#include "bossSkill.h"
#include "skillHandler.h"
#include "../AI/boss.h"
#include "../bar/rageBar.h"
#include "../../manager/textureManager.h"
#include "../../definition/gameState.h"
#include <SFML/Graphics.hpp>

using namespace game;

SkillHandler<BossSkill> BossSkill::handler;
std::map<BossSkill::Kind, std::map<BossSkill::State, std::string>> BossSkill::fileNames({
	std::pair(MultipleShoot
	, std::map<BossSkill::State, std::string>{
		std::pair(State::Using, "multipleShoot_using")
		, std::pair(State::Display, "multipleShoot_display")
		})
	});

BossSkill::BossSkill(const Kind skillName, const sf::Time &duration
	, std::vector<std::pair<Effect::Kind, bool>> && effects, std::vector<Attribute::Kind> && attributes
	, const bool exist, const std::shared_ptr<RageBar> rageBar, const Boss * boss)
	: SkillSystem(duration, exist)
	, skill(SkillContent{ skillName, State::Waiting, nullptr })
	, bInitialize(false)
	, m_rageBar(std::move(rageBar))
	, c_boss(boss) {
	// initialize effects
	std::for_each(effects.begin(), effects.end(), [&](const std::pair<Effect::Kind, bool> & effect) {
		skillEffects.push_back(std::make_shared<Effect>(effect.first, effect.second));
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
	if (skill.currentState == State::Waiting) return false;
	return skill.preview->getGlobalBounds().contains(point);
}

std::shared_ptr<sf::Drawable> BossSkill::getDrawable() const {
	return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
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

void BossSkill::onGameFinishedLevel(GameFinishedLevelEvent & event) {
	setState(State::Display);
}

void BossSkill::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (skill.currentState == State::Waiting) return;
	target.draw(*skill.preview, states);
}

void BossSkill::setState(const State nextState) {
	if (skill.currentState == nextState) return;
	// set skill preview
	if (nextState == State::Waiting) {
		skill.preview = nullptr;
	}
	else {
		auto stateTexture = TextureManager::getInstance().get(fileNames[skill.name][skill.currentState]);
		skill.preview.reset(new sf::Sprite(*stateTexture));
	}
	// set skill state
	skill.currentState = nextState;
}

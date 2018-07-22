#include "subPlayer.h"
#include "player.h"
#include "ball.h"
#include "../gameSys/level/level.h"
#include "../gameSys/bar/energyBar.h"
#include "../gameSys/bar/lifeBar.h"
#include "../gameSys/skill/subPlayerSkill.h"
#include "../manager/textureManager.h"
#include <SFML/Graphics.hpp>

using namespace game;

std::multimap<SubPlayer::Type, std::string> SubPlayer::partFileNames({
		std::pair(Prototype, "leftArmor")
		, std::pair(Prototype, "leftPinEngine")
		, std::pair(Prototype, "rightArmor")
		, std::pair(Prototype, "rightPinEngine")
		, std::pair(Prototype, "backArmor")
		, std::pair(Prototype, "frontArmor")
		, std::pair(Prototype, "frontCannon")
		, std::pair(Prototype, "centerChipConnector")
	});

SubPlayer::SubPlayer(const std::shared_ptr<Level> level)
	: energyBar(new EnergyBar(100, false, false, false))
	, lifeBar(new LifeBar(200, false, false, false))
	, key(new ControlKey)
	, bAutoUse(false)
	, m_level(level) {
	// set default type and chip setting
	changeType(item::Chip::None);
	// set default key setting
	defaultKeySettle();
	// set subPlayer skill
	subPlayerSkills = {
	};
}

void SubPlayer::update(const float updateRatio) {
	std::for_each(subPlayerSkills.begin(), subPlayerSkills.end()
		, [&](const std::shared_ptr<SubPlayerSkill> skill) {
		skill->update();
	});
}

void SubPlayer::setSubPlayerControlKey(const sf::Keyboard::Key upMove, const sf::Keyboard::Key downMove
	, const sf::Keyboard::Key leftMove, const sf::Keyboard::Key rightMove
	, const sf::Keyboard::Key attack, const sf::Keyboard::Key subSkill
	, const sf::Keyboard::Key subSkillSwap, const sf::Keyboard::Key turnSkillToTypeSkill
	, const sf::Keyboard::Key switchToPrevChargingSkill, const sf::Keyboard::Key switchToNextChargingSkill) {
	key->upMove = upMove;
	key->downMove = downMove;
	key->leftMove = leftMove;
	key->rightMove = rightMove;
	key->attack = attack;
	key->subSkill = subSkill;
	key->subSkillSwap = subSkillSwap;
	key->turnSkillToTypeSkill = turnSkillToTypeSkill;
	key->switchToPrevChargingSkill = switchToPrevChargingSkill;
	key->switchToNextChargingSkill = switchToNextChargingSkill;
}

void SubPlayer::changeType(const item::Chip::Kind chip) {
	using namespace item;
	// set pioneer type
	switch (chip) {
	case Chip::None:
		pioneer.currentType = Prototype;
		break;
	case Chip::BurstChip:
		break;
	case Chip::FirearmChip:
		break;
	case Chip::GuardChip:
		break;
	case Chip::HeraldChip:
		break;
	case Chip::LaserChip:
		break;
	default:
		throw std::invalid_argument("Wrong kind of chip");
	}
	// set pioneer chip
	pioneer.chip.reset(new Chip(chip));
}

void SubPlayer::addSubPlayerSkill(SubPlayerSkill && subPlayerSkill) {
	subPlayerSkills.push_back(std::make_shared<SubPlayerSkill>(subPlayerSkill));
}

bool SubPlayer::isAutoUse() const {
	return bAutoUse;
}

std::string SubPlayer::getType() const {
	switch (pioneer.currentType) {
	case Prototype:
		return "prototype_";
	default:
		throw std::out_of_range("Pioneer type no exist");
	}
}

item::Chip::Kind SubPlayer::getChip() const {
	return pioneer.chip->it;
}

const SubPlayer::ControlKey & SubPlayer::getKey() const {
	return *key;
}

void SubPlayer::resetCopyTarget(const std::shared_ptr<const Player> player, const std::shared_ptr<Ball> ball) {
	c_player = std::move(player);
	m_ball = std::move(ball);
}

SubPlayer::~SubPlayer() {
	removeAllChildren(true);
	removeAllListener();
}

void SubPlayer::setAutoUse(const bool isAutoUse) {
	bAutoUse = isAutoUse;
}

void SubPlayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	Container::draw(target, states);
}

void SubPlayer::defaultKeySettle() {
	using Key = sf::Keyboard::Key;
	if (m_level->isDefaultControlKeySettled()) return;
	if (m_level->getMode() == Mode::_2Player) {
		key->upMove = Key::W;
		key->downMove = Key::S;
		key->leftMove = Key::A;
		key->rightMove = Key::D;
		key->attack = Key::Unknown;
	}
	else {
		key->upMove = Key::Unknown;
		key->downMove = Key::Unknown;
		key->leftMove = Key::Unknown;
		key->rightMove = Key::Unknown;
		key->attack = Key::Unknown;
	}
	key->subSkill = Key::Unknown;
	key->subSkillSwap = Key::Unknown;
	key->turnSkillToTypeSkill = Key::Unknown;
	key->switchToPrevChargingSkill = Key::Unknown;
	key->switchToNextChargingSkill = Key::Unknown;
}

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

std::map<item::Chip::Kind, std::shared_ptr<sf::Texture>> SubPlayer::chipPreviews;

SubPlayer::SubPlayer(const std::shared_ptr<Level> level)
	: energyBar(new EnergyBar(100, false, false, false))
	, lifeBar(new LifeBar(200, false, false, false))
	, key()
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
	key = ControlKey{ upMove, downMove, leftMove, rightMove, attack };
	SubPlayerSkill::resetKey(subSkill, subSkillSwap, turnSkillToTypeSkill
		, switchToPrevChargingSkill, switchToNextChargingSkill);
}

void SubPlayer::changeType(const item::Chip::Kind chip) {
	using namespace item;
	// set pioneer type
	switch (chip) {
	case Chip::None:
		pioneer.currentType = Prototype;
		return;
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
	if (chip == Chip::None) { 
		pioneer.chip.reset(new Chip(chip));
	}
	else {
		pioneer.chip.reset(new Chip(chip, chipPreviews[chip]));
	}
}

void SubPlayer::addSubPlayerSkill(SubPlayerSkill && subPlayerSkill) {
	subPlayerSkills.push_back(std::make_shared<SubPlayerSkill>(subPlayerSkill));
}

void SubPlayer::loadChipPreviews(const std::map<item::Chip::Kind, std::string> & fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::pair<item::Chip::Kind, std::string> & file) {
		chipPreviews.emplace(file.first, TextureManager::getInstance().get(file.second));
		chipPreviews[file.first]->setSmooth(isSmooth);
	});
}

SubPlayer::Type SubPlayer::getType() const {
	return pioneer.currentType;
}

item::Chip::Kind SubPlayer::getChip() const {
	return pioneer.chip->it;
}

void SubPlayer::resetCopyTarget(const std::shared_ptr<const Player> player, const std::shared_ptr<Ball> ball) {
	c_player = std::move(player);
	m_ball = std::move(ball);
}

SubPlayer::~SubPlayer() {
	removeAllChildren(true);
	removeAllListener();
}

void SubPlayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	Container::draw(target, states);
}

void SubPlayer::defaultKeySettle() {
	using Key = sf::Keyboard::Key;
	if (m_level->isDefaultControlKeySettled()) return;
	if (m_level->getMode() == Mode::_2Player) {
		key = ControlKey{ Key::W, Key::S, Key::A, Key::D, Key::Unknown };
	}
	else {
		key = ControlKey{ Key::Unknown, Key::Unknown, Key::Unknown, Key::Unknown, Key::Unknown };
	}
	SubPlayerSkill::resetKey(Key::Unknown, Key::Unknown, Key::Unknown, Key::Unknown, Key::Unknown);
}

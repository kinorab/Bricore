#include "subPlayer.h"
#include "player.h"
#include "ball.h"
#include "../gameSys/level/level.h"
#include "../gameSys/bar/energyBar.h"
#include "../gameSys/bar/lifeBar.h"
#include "../gameSys/skill/subPlayerSkill.h"
#include "../event/SFMLMouseHandler.h"
#include "../event/SFMLKeyboardHandler.h"
#include <SFML/Graphics.hpp>

using namespace game;

SubPlayer::SubPlayer(const std::shared_ptr<Level> level)
	: energyBar(new EnergyBar(100, false, false, false))
	, lifeBar(new LifeBar(200, false, false, false))
	, m_level(level) {
	defaultKeySettle();
	subPlayerSkills = {
	};
}

void SubPlayer::update(const float intervalRate) {
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

void SubPlayer::addSubPlayerSkill(game::SubPlayerSkill && subPlayerSkill) {
	subPlayerSkills.push_back(std::make_shared<SubPlayerSkill>(subPlayerSkill));
}

void SubPlayer::resetCopyTarget(const std::shared_ptr<const Player> player, const std::shared_ptr<Ball> ball) {
	c_player = std::move(player);
	m_ball = std::move(ball);
}

void SubPlayer::handle(const sf::Event & event) {
	mouseHandler->handle(event, *this, false);
	keyboardHandler->handle(event, *this);
	std::for_each(subPlayerSkills.begin(), subPlayerSkills.end()
		, [&](const std::shared_ptr<SubPlayerSkill> skill) {
		skill->handleSelect(&event);
		skill->handleSkill(&event);
	});
}

SubPlayer::~SubPlayer() {
	removeAllChildren();
}

void SubPlayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
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

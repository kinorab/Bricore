#include "boss.h"
#include "../skill/bossSkill.h"
#include "../../manager/textureManager.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>

using namespace game;
using namespace item;

bool Boss::bDisplay(false);
// partName
// intense_partName
// intense_partName_intensified
// weak_partName
// weak_partName_broke
std::multimap<Boss::Name, std::string> Boss::partFileNames({
		std::pair(Punece, "leftSmashGlove")
		, std::pair(Punece, "leftArm")
		, std::pair(Punece, "leftArmConnector")
		, std::pair(Punece, "leftArmor")
		, std::pair(Punece, "rightSmashGlove")
		, std::pair(Punece, "rightArm")
		, std::pair(Punece, "rightArmor")
		, std::pair(Punece, "rightArmConnector")
		, std::pair(Punece, "centerArmor")
		, std::pair(Punece, "weak_backArmor")
		, std::pair(Punece, "weak_backArmor_broke")
		, std::pair(Punece, "weak_frontArmor")
		, std::pair(Punece, "weak_frontArmor_broke")
	});

Boss::Boss(const Name name, const Core::Kind core, const Attribute::Kind attribute
	, std::vector<BossSkill> && skills, const size_t maxSkillOnUsing)
	: boss(BossContent{ name, maxSkillOnUsing, std::make_shared<Core>(core)
		, std::make_shared<Attribute>(attribute), {}, {}, {}, {} })
	, bAlive(false)
	, bDebut(false)
	, bMove(false) {
	// initialize skills
	std::for_each(skills.begin(), skills.end(), [&](const BossSkill &skill) {
		boss.skills.push_back(std::make_shared<BossSkill>(skill));
	});
}

bool Boss::containsPoint(const sf::Vector2f & point) const {
	if (!bDebut && !bDisplay) return false;
	// core
	if (boss.core->containsPoint(point)) return true;
	if (!bAlive && !bDisplay) return false;
	// part
	for (auto & part : boss.parts) {
		if (part.second.context->getGlobalBounds().contains(point)) return true;
	}
	for (auto & intensePart : boss.intenseParts) {
		if (intensePart.second.context->getGlobalBounds().contains(point)) return true;
	}
	for (auto & weakPart : boss.weakParts) {
		if (weakPart.second.context->getGlobalBounds().contains(point)) return true;
	}
	// skill first
	for (auto & skill : boss.skills) {
		if (skill->containsPoint(point)) return true;
	}
	return false;
}

void Boss::update(const float updateRatio) {
}

/*void Boss::offset(const sf::Vector2f &offset, const sf::Time &moveTime) {
	static sf::Time duration = sf::seconds(0);
	if (duration <= sf::seconds(0)) duration = moveTime;
	boss.core->setPosition(boss.core->getPosition() + offset);
	std::for_each(boss.parts.begin(), boss.parts.end()
		, [=](const std::pair<std::string, Part> &element) {
		element.second.context->setPosition(element.second.context->getPosition() + offset);
	});
	std::for_each(boss.weakParts.begin(), boss.weakParts.end()
		, [=](const std::pair<std::string, WeakPart> &element) {
		element.second.context->setPosition(element.second.context->getPosition() + offset);
	});
	duration -= clock.restart();
}

void Boss::moveTo(const sf::Vector2f &coordinate, const sf::Time &moveTime) {
	static sf::Time duration = sf::seconds(0);

	if (boss.core->getPosition() == coordinate) return;
	sf::Vector2f displacement = coordinate - boss.core->getPosition();
	boss.core->setPosition(boss.core->getPosition() + displacement);
	std::for_each(boss.parts.begin(), boss.parts.end()
		, [=](const std::pair<std::string, Part> &element) {
		element.second.context->setPosition(element.second.context->getPosition() + displacement);
	});
	std::for_each(boss.weakParts.begin(), boss.weakParts.end()
		, [=](const std::pair<std::string, WeakPart> &element) {
		element.second.context->setPosition(element.second.context->getPosition() + displacement);
	});
	duration -= clock.restart();
}*/

void Boss::setDisplay(const bool isDisplay) {
	bDisplay = isDisplay;
}

void Boss::addBossSkill(BossSkill && bossSkill) {
	boss.skills.push_back(std::make_shared<BossSkill>(bossSkill));
}

void Boss::extendMaxOnUsing(const size_t number) {
	boss.maxOnUsingSkill += number;
}

Attribute::Kind Boss::getAttribute() const {
	return boss.attribute->it;
}

Core::Kind Boss::getCore() const {
	return boss.core->it;
}

bool Boss::isDisplay() {
	return bDisplay;
}

std::string Boss::getName() const {
	switch (boss.bossName) {
	case Punece:
		return "punece_";
	case Felifice:
		return "felifice_";
	case Apache:
		return "apache_";
	default:
		throw std::out_of_range("Boss name no exist.");
	}
}

size_t Boss::getMaxOnUsing() const {
	return boss.maxOnUsingSkill;
}

size_t Boss::getPartAmount() const {
	return boss.parts.size();
}

size_t Boss::getIntensePartAmount() const {
	return boss.intenseParts.size();
}

size_t Boss::getIntensifiedPartAmount() const {
	size_t number = 0;
	for (const auto &element : boss.intenseParts) {
		if (element.second.bIntensified) ++number;
	}
	return number;
}

size_t Boss::getWeakPartAmount() const {
	return boss.weakParts.size();
}

size_t Boss::getBrokenPartAmount() const {
	size_t number = 0;
	for (const auto &element : boss.weakParts) {
		if (element.second.bBroke) ++number;
	}
	return number;
}

bool Boss::isAlive() const {
	return bAlive;
}

bool Boss::isDebut() const {
	return bDebut;
}

Boss::~Boss() {
}

Boss::Boss(const Boss & copy)
	: boss(copy.boss)
	, bMove(copy.bMove)
	, bDebut(copy.bDebut)
	, bAlive(copy.bAlive) {
}

#pragma warning(suppress: 26434)
Boss & Boss::operator =(Boss copy) {
	boss = std::move(copy.boss);
	bMove = copy.bMove;
	bAlive = copy.bAlive;
	bDebut = copy.bDebut;
	return *this;
}

void Boss::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (!bDebut && !bDisplay) return;
	// core draw
	target.draw(*boss.core, states);
	if (!bAlive && !bDisplay) return;
	// part draw
	std::for_each(boss.parts.begin(), boss.parts.end()
		, [&](const std::pair<std::string, Part> & element) {
		target.draw(*element.second.context, states);
	});
	std::for_each(boss.intenseParts.begin(), boss.intenseParts.end()
		, [&](const std::pair<std::string, IntensePart> & element) {
		target.draw(*element.second.context, states);
	});
	std::for_each(boss.weakParts.begin(), boss.weakParts.end()
		, [&](const std::pair<std::string, WeakPart> &element) {
		target.draw(*element.second.context, states);
	});
	// skill draw
	std::for_each(boss.skills.begin(), boss.skills.end()
		, [&](const std::shared_ptr<BossSkill> skill) {
		target.draw(*skill, states);
	});
}

void Boss::debut() {
	if (bDebut) return;
	resettleParts();
	clock.restart();
	bDebut = true;
	bAlive = true;
}

void Boss::changeCore(const Core::Kind type) {
	boss.core.reset(new Core(type));
}

void Boss::weakPartBreak(const std::string & weak_partName) {
	auto iter = boss.weakParts.find(weak_partName);
	if (iter == boss.weakParts.end()) throw std::invalid_argument("Weak part no found.");
	if (iter->second.bBroke) throw std::exception("Weak part was already broken.");
	iter->second.bBroke = true;
	auto weakPartTexture = TextureManager::getInstance().get(getName() + weak_partName + "_broke");
	iter->second.context.reset(new sf::Sprite(*weakPartTexture));
}

void Boss::weakPartRecover(const std::string & weak_partName) {
	auto iter = boss.weakParts.find(weak_partName);
	if (iter == boss.weakParts.end()) throw std::invalid_argument("Weak part no found.");
	if (!iter->second.bBroke) throw std::exception("Weak part was already recovered.");
	iter->second.bBroke = false;
	auto weakPartTexture = TextureManager::getInstance().get(getName() + weak_partName);
	iter->second.context.reset(new sf::Sprite(*weakPartTexture));
}

void Boss::partIntensify(const std::string & intense_partName) {
	auto iter = boss.intenseParts.find(intense_partName);
	if (iter == boss.intenseParts.end()) throw std::invalid_argument("Part no found.");
	if (iter->second.bIntensified) throw std::exception("Part was already intensified.");
	iter->second.bIntensified = true;
	auto intenseTexture = TextureManager::getInstance().get(getName() + intense_partName + "_intensified");
	iter->second.context.reset(new sf::Sprite(*intenseTexture));
}

void Boss::partRecover(const std::string & intense_partName) {
	auto iter = boss.intenseParts.find(intense_partName);
	if (iter == boss.intenseParts.end()) throw std::invalid_argument("Part no found.");
	if (!iter->second.bIntensified) throw std::exception("Part was already recovered.");
	iter->second.bIntensified = false;
	auto intenseTexture = TextureManager::getInstance().get(getName() + intense_partName);
	iter->second.context.reset(new sf::Sprite(*intenseTexture));
}

void Boss::resettleParts() {
	boss.parts.clear();
	boss.weakParts.clear();
	boss.intenseParts.clear();
	auto partFiles = partFileNames.equal_range(boss.bossName);
	std::for_each(partFiles.first, partFiles.second
		, [this](const std::pair<Name, std::string> & part) {
		if (part.second.find("_broke") != std::string::npos
			|| part.second.find("_intensified") != std::string::npos) return;
		// set weak part
		if (part.second.find("weak_") != std::string::npos) {
			// (boss name + part name) ensure directory correct
			auto weakPartTexture = TextureManager::getInstance().get(getName() + part.second);
			boss.weakParts.emplace(part.second, WeakPart{ std::make_shared<sf::Sprite>(*weakPartTexture), false });
		}
		// set intense part
		else if (part.second.find("intense_") != std::string::npos) {
			// (boss name + part name) ensure directory correct
			auto intensePartTexture = TextureManager::getInstance().get(getName() + part.second);
			boss.intenseParts.emplace(part.second, IntensePart{ std::make_shared<sf::Sprite>(*intensePartTexture), false });
		}
		// set normal part
		else {
			// (boss name + part name) ensure directory correct
			auto partTexture = TextureManager::getInstance().get(getName() + part.second);
			boss.parts.emplace(part.second, Part{ std::make_shared<sf::Sprite>(*partTexture) });
		}
	});
}

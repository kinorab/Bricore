#include "boss.h"
#include "../skill/bossSkill.h"
#include "../../manager/textureManager.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>

using namespace game;

std::map<item::Core::Kind, std::shared_ptr<sf::Texture>> Boss::corePreviews;

Boss::Boss(const std::string name, const Attribute::Kind &attribute
	, const std::vector<BossSkill> &skills, const size_t maxSkillOnUsing)
	: boss(BossContent{ name, maxSkillOnUsing, nullptr
		, std::make_shared<Attribute>(attribute), {}, {}, {} })
	, bExist(false)
	, bMove(false) {
	// initialize skills
	std::for_each(skills.begin(), skills.end(), [&](const BossSkill &skill) {
		boss.skills.push_back(std::make_shared<BossSkill>(skill));
	});
}

bool Boss::containsPoint(const sf::Vector2f & point) const {
	if (!bExist) return false;
	if (boss.core->containsPoint(point)) return true;
	for (auto & part : boss.parts) {
		if (part.second.context->getGlobalBounds().contains(point)) return true;
	}
	for (auto & weakPart : boss.weakParts) {
		if (weakPart.second.context->getGlobalBounds().contains(point)) return true;
	}
	return false;
}

void Boss::loadCorePreviews(const std::map<item::Core::Kind, std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::pair<item::Core::Kind, std::string> &file) {
		corePreviews.emplace(file.first, TextureManager::getInstance().get(file.second));
		corePreviews.at(file.first)->setSmooth(isSmooth);
	});
}

void Boss::loadPartPreviews(const std::vector<std::string>& fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::string &file) {
		partPreviews.emplace(file, TextureManager::getInstance().get(file));
		partPreviews.at(file)->setSmooth(isSmooth);
	});
}

void Boss::update(const float updateRatio) {
}

void Boss::handle(const sf::Event & event) {

}

void Boss::offset(const sf::Vector2f &offset, const sf::Time &moveTime) {
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

item::Core::Kind Boss::getBossCore() const {
	return boss.core->it;
}

const std::string & Boss::getBossName() const {
	return boss.bossName;
}

size_t Boss::getMaxOnUsing() const {
	return boss.maxOnUsingSkill;
}

size_t Boss::getPartAmount() const {
	return boss.parts.size();
}

size_t Boss::getIntensifiedPartAmount() const {
	size_t number = 0;
	for (const auto &element : boss.parts) {
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

bool Boss::isExist() const {
	return bExist;
}

Boss::~Boss() {
}

Boss::Boss(const Boss & copy)
	: boss(copy.boss)
	, partPreviews(copy.partPreviews)
	, bMove(copy.bMove)
	, bExist(copy.bExist) {
}

Boss & Boss::operator =(Boss copy) {
	boss = std::move(copy.boss);
	partPreviews.swap(copy.partPreviews);
	bMove = copy.bMove;
	bExist = copy.bExist;
	return *this;
}

void Boss::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (bExist) return;
	target.draw(*boss.core, states);
	std::for_each(boss.parts.begin(), boss.parts.end()
		, [&](const std::pair<std::string, Part> &element) {
		target.draw(*element.second.context, states);
	});
	std::for_each(boss.weakParts.begin(), boss.weakParts.end()
		, [&](const std::pair<std::string, WeakPart> &element) {
		target.draw(*element.second.context, states);
	});
	std::for_each(boss.skills.begin(), boss.skills.end()
		, [&](const std::shared_ptr<BossSkill> skill) {
		target.draw(*skill, states);
	});
}

void Boss::debut(const item::Core::Kind type) {
	std::for_each(partPreviews.begin(), partPreviews.end()
		, [this](const std::pair<std::string, std::shared_ptr<sf::Texture>> element) {
		if (element.first.find("_broke") != std::string::npos
			|| element.first.find("_intense") != std::string::npos) return;
		if (element.first.find("weak_") == std::string::npos) {
			boss.parts.emplace(element.first
				, Part{ std::make_shared<sf::Sprite>(*element.second), false });
			auto & part = boss.parts.at(element.first).context;
			part->setOrigin(part->getLocalBounds().width / 2.f, part->getLocalBounds().height / 2.f);
			return;
		}
		boss.weakParts.emplace(element.first
			, WeakPart{ std::make_shared<sf::Sprite>(*element.second), false });
		auto & weakPart = boss.weakParts.at(element.first).context;
		weakPart->setOrigin(weakPart->getLocalBounds().width / 2.f, weakPart->getLocalBounds().height / 2.f);
	});
	boss.core.reset(new item::Core(type, corePreviews.at(type)));
	boss.core->setOrigin( boss.core->getLocalBounds().width / 2.f
		, boss.core->getLocalBounds().height / 2.f );
	clock.restart();
	bExist = true;
}

void Boss::changeCore(const item::Core::Kind type) {
	if (!bExist) throw std::invalid_argument("Boss not exist.");
	boss.core.reset(new item::Core(type, corePreviews.at(type)));
	boss.core->setOrigin( boss.core->getLocalBounds().width / 2.f, boss.core->getLocalBounds().height / 2.f );
}

void Boss::weakPartBreak(const std::string & weak_partName) {
	auto iter = boss.weakParts.find(weak_partName);
	if (iter == boss.weakParts.end()) throw std::invalid_argument("Weak part no found.");
	if (iter->second.bBroke) throw std::exception("Weak part was already broken.");
	iter->second.bBroke = true;
	iter->second.context.reset(new sf::Sprite(*partPreviews.at(weak_partName + "_broke")));
}

void Boss::weakPartRecover(const std::string & weak_partName) {
	auto iter = boss.weakParts.find(weak_partName);
	if (iter == boss.weakParts.end()) throw std::invalid_argument("Weak part no found.");
	if (!iter->second.bBroke) throw std::exception("Weak part was already recovered.");
	iter->second.bBroke = false;
	iter->second.context.reset(new sf::Sprite(*partPreviews.at(weak_partName)));
}

void Boss::partIntensify(const std::string & partName) {
	auto iter = boss.parts.find(partName);
	if (iter == boss.parts.end()) throw std::invalid_argument("Part no found.");
	if (iter->second.bIntensified) throw std::exception("Part was already intensified.");
	iter->second.bIntensified = true;
	iter->second.context.reset(new sf::Sprite(*partPreviews.at(partName + "_intense")));
}

void Boss::partRecover(const std::string & partName) {
	auto iter = boss.parts.find(partName);
	if (iter == boss.parts.end()) throw std::invalid_argument("Part no found.");
	if (!iter->second.bIntensified) throw std::exception("Part was already recovered.");
	iter->second.bIntensified = false;
	iter->second.context.reset(new sf::Sprite(*partPreviews.at(partName)));
}

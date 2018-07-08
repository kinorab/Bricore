#include "boss.h"
#include "../skill/bossSkill.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>

using namespace game;

std::map<item::Core::Kind, std::shared_ptr<sf::Texture>> Boss::coreTypePreviews;

Boss::Boss(const std::string name, const Attribute::Kind &attribute
	, const std::vector<BossSkill> &skills, const size_t maxOnUsingSkill)
	: boss(CoreType{ name, nullptr, nullptr }
		, Content{ maxOnUsingSkill, std::shared_ptr<Attribute>(new Attribute(attribute)), {}, {}, {} })
	, bExist(false)
	, bMove(false) {
	std::for_each(skills.begin(), skills.end(), [&](const BossSkill &skill) {
		boss.second.skills.push_back(std::shared_ptr<BossSkill>(new BossSkill(skill)));
	});
}

void Boss::loadCoreTypePreviews(const std::map<item::Core::Kind, std::string> &fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::pair<item::Core::Kind, std::string> &file) {
		coreTypePreviews.emplace(file.first, std::shared_ptr<sf::Texture>(new sf::Texture));
		coreTypePreviews.at(file.first)->loadFromFile(file.second);
		coreTypePreviews.at(file.first)->setSmooth(isSmooth);
	});
}

void Boss::loadPartPreviews(const std::vector<std::string>& fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::string &file) {
		partPreviews.emplace(file, std::shared_ptr<sf::Texture>(new sf::Texture));
		partPreviews.at(file)->loadFromFile(file);
		partPreviews.at(file)->setSmooth(isSmooth);
	});
}

void Boss::update(const float updateRatio) {
}

void Boss::handle(const sf::Event * const event) {

}

void Boss::offset(const sf::Vector2f &offset, const sf::Time &moveTime) {
	static sf::Time duration = sf::seconds(0);
	if (duration <= sf::seconds(0)) duration = moveTime;
	boss.first.context->setPosition(boss.first.context->getPosition() + offset);
	std::for_each(boss.second.parts.begin(), boss.second.parts.end()
		, [=](const std::pair<std::string, Part> &element) {
		element.second.context->setPosition(element.second.context->getPosition() + offset);
	});
	std::for_each(boss.second.weakParts.begin(), boss.second.weakParts.end()
		, [=](const std::pair<std::string, WeakPart> &element) {
		element.second.context->setPosition(element.second.context->getPosition() + offset);
	});
	duration -= clock.restart();
}

void Boss::moveTo(const sf::Vector2f &coordinate, const sf::Time &moveTime) {
	static sf::Time duration = sf::seconds(0);

	if (boss.first.context->getPosition() == coordinate) return;
	sf::Vector2f displacement = coordinate - boss.first.context->getPosition();
	boss.first.context->setPosition(boss.first.context->getPosition() + displacement);
	std::for_each(boss.second.parts.begin(), boss.second.parts.end()
		, [=](const std::pair<std::string, Part> &element) {
		element.second.context->setPosition(element.second.context->getPosition() + displacement);
	});
	std::for_each(boss.second.weakParts.begin(), boss.second.weakParts.end()
		, [=](const std::pair<std::string, WeakPart> &element) {
		element.second.context->setPosition(element.second.context->getPosition() + displacement);
	});
	duration -= clock.restart();
}

void Boss::extendMaxOnUsing(const size_t number) {
	boss.second.maxOnUsing += number;
}

Attribute::Kind Boss::getAttribute() const {
	return boss.second.attribute->it;
}

item::Core::Kind Boss::getBossCoreType() const {
	return boss.first.core->type;
}

const std::string & Boss::getBossName() const {
	return boss.first.bossName;
}

size_t Boss::getMaxOnUsing() const {
	return boss.second.maxOnUsing;
}

size_t Boss::getPartAmount() const {
	return boss.second.parts.size();
}

size_t Boss::getIntensifiedPartAmount() const {
	size_t number = 0;
	for (const auto &element : boss.second.parts) {
		if (element.second.intensified) ++number;
	}
	return number;
}

size_t Boss::getWeakPartAmount() const {
	return boss.second.weakParts.size();
}

size_t Boss::getBrokenPartAmount() const {
	size_t number = 0;
	for (const auto &element : boss.second.weakParts) {
		if (element.second.broke) ++number;
	}
	return number;
}

size_t Boss::getCoreTypeAmount() {
	return coreTypePreviews.size();
}

bool Boss::isExist() const {
	return bExist;
}

Boss::~Boss() {
}

Boss::Boss(const Boss & copy)
	: boss(copy.boss) {
}

Boss & Boss::operator =(Boss copy) {
	boss.swap(copy.boss);
	return *this;
}

void Boss::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (bExist) {
		states.transform *= getTransform();
		target.draw(*boss.first.context, states);
		std::for_each(boss.second.parts.begin(), boss.second.parts.end()
			, [&](const std::pair<std::string, Part> &element) {
			target.draw(*element.second.context, states);
		});
		std::for_each(boss.second.weakParts.begin(), boss.second.weakParts.end()
			, [&](const std::pair<std::string, WeakPart> &element) {
			target.draw(*element.second.context, states);
		});
		std::for_each(boss.second.skills.begin(), boss.second.skills.end()
			, [&](const std::shared_ptr<BossSkill> skill) {
			target.draw(*skill, states);
		});
	}
}

void Boss::debut(const item::Core::Kind type) {
	std::for_each(partPreviews.begin(), partPreviews.end()
		, [this](const std::pair<std::string, std::shared_ptr<sf::Texture>> element) {
		if (element.first.find("_broke") != std::string::npos
			|| element.first.find("_intense") != std::string::npos) return;
		if (element.first.find("weak_") == std::string::npos) {
			boss.second.parts.emplace(element.first
				, Part{ std::shared_ptr<sf::Sprite>(new sf::Sprite(*element.second)), false });
			auto part = boss.second.parts.at(element.first).context;
			part->setOrigin(part->getTextureRect().width / 2.f, part->getTextureRect().height / 2.f);
			return;
		}
		boss.second.weakParts.emplace(element.first
			, WeakPart{ std::shared_ptr<sf::Sprite>(new sf::Sprite(*element.second)), false });
		auto weakPart = boss.second.weakParts.at(element.first).context;
		weakPart->setOrigin(weakPart->getTextureRect().width / 2.f, weakPart->getTextureRect().height / 2.f);
	});
	boss.first.context.reset(new sf::Sprite(*coreTypePreviews.at(type)));
	boss.first.core.reset(new item::Core(type));
	auto core = boss.first.context;
	core->setOrigin(core->getTextureRect().width / 2.f, core->getTextureRect().height / 2.f);
	clock.restart();
	bExist = true;
}

void Boss::changeCoreType(const item::Core::Kind type) {
	if (!bExist) throw std::invalid_argument("Boss not exist.");
	boss.first.context.reset(new sf::Sprite(*coreTypePreviews.at(type)));
	boss.first.core.reset(new item::Core(type));
	auto core = boss.first.context;
	core->setOrigin(core->getTextureRect().width / 2.f, core->getTextureRect().height / 2.f);
}

void Boss::weakPartBreak(const std::string & weak_partName) {
	auto iter = boss.second.weakParts.find(weak_partName);
	if (iter == boss.second.weakParts.end()) throw std::invalid_argument("Weak part no found.");
	if (iter->second.broke) throw std::exception("Weak part was already broken.");
	iter->second.broke = true;
	iter->second.context.reset(new sf::Sprite(*partPreviews.at(weak_partName + "_broke")));
}

void Boss::weakPartRecover(const std::string & weak_partName) {
	auto iter = boss.second.weakParts.find(weak_partName);
	if (iter == boss.second.weakParts.end()) throw std::invalid_argument("Weak part no found.");
	if (!iter->second.broke) throw std::exception("Weak part was already recovered.");
	iter->second.broke = false;
	iter->second.context.reset(new sf::Sprite(*partPreviews.at(weak_partName)));
}

void Boss::partIntensify(const std::string & partName) {
	auto iter = boss.second.parts.find(partName);
	if (iter == boss.second.parts.end()) throw std::invalid_argument("Part no found.");
	if (iter->second.intensified) throw std::exception("Part was already intensified.");
	iter->second.intensified = true;
	iter->second.context.reset(new sf::Sprite(*partPreviews.at(partName + "_intense")));
}

void Boss::partRecover(const std::string & partName) {
	auto iter = boss.second.parts.find(partName);
	if (iter == boss.second.parts.end()) throw std::invalid_argument("Part no found.");
	if (!iter->second.intensified) throw std::exception("Part was already recovered.");
	iter->second.intensified = false;
	iter->second.context.reset(new sf::Sprite(*partPreviews.at(partName)));
}

#include "barSystem.h"
#include <stdexcept>
#include <iostream>

using namespace game;

BarSystem::BarSystem(const size_t maxCount, const bool appear, const bool numberVisible, const bool exist)
	: System(false)
	, uMaxCount(maxCount)
	, uCurrentCount(0)
	, bStatisticVisible(numberVisible)
	, bAppear(appear)
	, bExist(exist) {
}

void BarSystem::setStatisticVisible(const bool visible) {
	bStatisticVisible = visible;
}

void BarSystem::extendMaxCount(const size_t count) {
	uMaxCount += count;
}

bool BarSystem::isFull() const {
	if (uCurrentCount == uMaxCount) return true;
	return false;
}

bool BarSystem::isExist() const {
	return bExist;
}

size_t BarSystem::getMaxCount() const {
	return uMaxCount;
}

size_t BarSystem::getCurrentCount() const {
	return uCurrentCount;
}

float BarSystem::getCountPercentage() const {
	return (static_cast<float>(uCurrentCount) / static_cast<float>(uMaxCount)) * 100.f;
}

BarSystem::~BarSystem() {
}


#pragma warning(suppress: 26434)
void BarSystem::setEnable(const bool enable) {
	if (!bExist) throw std::invalid_argument("Bar not exist.");
	if (isEnable() == enable) return;
	System::setEnable(enable);
}

void BarSystem::setExist(const bool exist) {
	try {
		if (isEnable()) throw std::invalid_argument("Bar is still enabled.");
		this->bExist = exist;
	}
	catch (std::invalid_argument &ex) {
		std::cout << ex.what() << std::endl;
		setEnable(false);
	}
}

void BarSystem::clear() {
	if (!bExist) throw std::invalid_argument("Bar not exist.");
	uCurrentCount = 0;
}

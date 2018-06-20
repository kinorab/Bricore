#include "barSystem.h"
#include <stdexcept>
#include <iostream>

using namespace game;

BarSystem::BarSystem(const size_t maxCount, const bool debut, const bool numberVisible, const bool exist)
	: System(false)
	, maxCount(maxCount)
	, currentCount(0)
	, statisticVisible(numberVisible)
	, debut(debut)
	, exist(exist) {
}

void BarSystem::setStatisticVisible(const bool visible) {
	statisticVisible = visible;
}

void BarSystem::extendMaxCount(const size_t count) {
	maxCount += count;
}

bool BarSystem::isFull() const {
	if (currentCount == maxCount) return true;
	return false;
}

bool BarSystem::isExist() const {
	return exist;
}

size_t BarSystem::getMaxCount() const {
	return maxCount;
}

size_t BarSystem::getCurrentCount() const {
	return currentCount;
}

float BarSystem::getCountPercentage() const {
	return (static_cast<float>(currentCount) / static_cast<float>(maxCount)) * 100.f;
}

BarSystem::~BarSystem() {
}


void BarSystem::setEnable(const bool enable) {
	if (!exist) throw std::invalid_argument("Bar not exist.");
	if (isEnable() == enable) return;
	System::setEnable(enable);
}

void BarSystem::setExist(const bool exist) {
	try {
		if (isEnable()) throw std::invalid_argument("Bar is still enabled.");
		this->exist = exist;
	}
	catch (std::invalid_argument &ex) {
		std::cout << ex.what() << std::endl;
		setEnable(false);
	}
}

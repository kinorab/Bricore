#include "system.h"

using namespace game;

System::~System() {
}

const bool & System::isEnable() const {
	return enable;
}

System::System(const bool enable) 
	: enable(enable) {
}

void System::setEnable(const bool enable) {
	this->enable = enable;
}

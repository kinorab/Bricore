#include "system.h"

using namespace game;

System::~System() {
}

const bool & System::isEnable() const {
	return bEnable;
}

System::System(const bool enable) 
	: bEnable(enable) {
}

void System::setEnable(const bool enable) {
	if (bEnable == enable) return;
	this->bEnable = enable;
}

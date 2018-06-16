#include "area.h"
#include "effect/normalEffect.h"

namespace game {
	void Area::update() {
	}

	bool Area::isAOEempty(const std::string name) const {
		return AOEs.at(name).empty();
	}

	Area::~Area() {
	}
}

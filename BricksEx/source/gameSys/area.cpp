#include "area.h"
#include "effect/normalEffect.h"

void game::Area::update() {
}

bool game::Area::isAOEempty(const std::string name) const {
	return AOEs.at(name).empty();
}

game::Area::~Area() {
}

#include "area.h"
#include "../gameSys/effect/effect.h"

void game::Area::update() {
}

bool game::Area::isAOEempty(const std::string name) const {
	return AOEs.at(name).empty();
}

game::Area::~Area() {
}

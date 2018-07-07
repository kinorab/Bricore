#include "attribute.h"

using namespace game;

Attribute::Attribute(const Kind element)
	: effect(static_cast<Effect>(element))
	, element(element) {
}

Attribute::~Attribute() {
}

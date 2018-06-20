#include "effect.h"

using namespace game;

Effect::Effect(const Kind kind) 
	: content(kind) {
}

Effect::Kind Effect::getEffect() const {
	return content;
}

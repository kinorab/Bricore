#include "effect.h"

using namespace game;

Effect::Effect(const Kind kind) noexcept
	: content(kind) {
}

Effect::~Effect() {
}

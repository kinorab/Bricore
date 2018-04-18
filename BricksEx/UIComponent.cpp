#include "UIComponent.h"

bool game::UIComponent::getEnabled() const {
	return enabled;
}

void game::UIComponent::setEnabled(bool value) {
	enabled = value;
}

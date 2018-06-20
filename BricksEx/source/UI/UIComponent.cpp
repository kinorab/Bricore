#include "UIComponent.h"

namespace game {
	bool UIComponent::getEnabled() const {
		return enabled;
	}

	void UIComponent::setEnabled(bool value) {
		enabled = value;
	}
}

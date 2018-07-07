#include "UIComponent.h"

namespace game {
	bool UIComponent::getEnabled() const {
		return bEnabled;
	}

	void UIComponent::setEnabled(bool value) {
		bEnabled = value;
	}
}

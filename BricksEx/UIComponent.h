#pragma once

#include "container.h"

namespace game {
	class UIComponent
		: public game::Container {
	public:
		virtual ~UIComponent() {}
		virtual bool getEnabled() const;
		virtual void setEnabled(bool value);
	private:
		bool enabled;
	};
}
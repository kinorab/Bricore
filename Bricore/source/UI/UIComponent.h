#pragma once

#include "../interact/container.h"

namespace game {
	class UIComponent
		: public Container {
	public:
		virtual ~UIComponent() {}
		virtual bool getEnabled() const;
		virtual void setEnabled(bool value);
	private:
		bool bEnabled = false;
	};
}
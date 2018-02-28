#pragma once

#include "container.h"

class UIComponent :
	public virtual Container {
public:
	virtual ~UIComponent() {}
};
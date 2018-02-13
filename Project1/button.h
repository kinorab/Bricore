#pragma once

#include "UIComponent.h"

class Button :
	public virtual UIComponent {
public:
	virtual ~Button() { }
	virtual void checkClick(sf::Vector2f mousePos) = 0;
	virtual void setCaption(std::string caption) = 0;
	virtual std::string getCaption() = 0;
};
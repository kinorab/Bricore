#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class ButtonInterface {
public:
	virtual ~ButtonInterface() = 0;
};

ButtonInterface::~ButtonInterface() {

}

class bb : ButtonInterface{

};
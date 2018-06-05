#pragma once

#include "isBaseOfTemplate.h"

template<typename Type>
class Visitable {
public:
	virtual void accept(Type * visitor) = 0;
};

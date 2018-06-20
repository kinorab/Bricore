#pragma once

template<typename Type>
class Visitable {
public:
	virtual void accept(Type & visitor) = 0;
};

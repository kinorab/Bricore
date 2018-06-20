#pragma once

template<typename Type>
class AcyclicVisitable {
public:
	virtual void accept(Type & visitor) = 0;
};

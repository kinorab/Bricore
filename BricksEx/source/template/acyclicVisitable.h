#pragma once

template<typename Type>
class AcyclicVisitable {
public:
	virtual void accept(Type * visitor) = 0;
protected:
	virtual void visitFailedHandler() = 0;
};

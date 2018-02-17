#pragma once
class EventDispatcher
{
public:
	virtual ~EventDispatcher() {};
	virtual void addEventListener() = 0;
	virtual bool hasEventListener() = 0;
	virtual void removeEventListener() = 0;
};

#pragma once
class Observer
{
public:
	Observer(void);
	~Observer(void);

	virtual void update() = 0;
};


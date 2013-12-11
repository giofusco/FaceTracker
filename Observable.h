#pragma once

#include<vector>
#include "Observer.h"
class Observable
{
public:
	Observable(void);
	~Observable(void);

	void attach(Observer* o){ observers.push_back(o); };
	void detach(Observer* o){ observers.erase(std::find(observers.begin(),observers.end(),o)); };
	void notify(){ for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it) (*it)->update();};

protected:
	std::vector<Observer*> observers;

};


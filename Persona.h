#pragma once
#include "trackable.h"
class Persona :
	public Trackable
{
public:
	Persona(Rect roi):Trackable(roi){;};
	
	~Persona(void);

	void updateStatus(){ 
		Trackable::updateStatus();
		describeFrame();
	}

protected:
	void describeFrame();
	
};


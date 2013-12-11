#pragma once

#include "Trackable.h"

class TrackerPolicy
{
public:
	TrackerPolicy(void);
	~TrackerPolicy(void);
	virtual std::vector<Trackable*> execute(std::vector<Rect> rois, std::vector<Trackable*> tracked) = 0;

};


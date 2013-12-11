#pragma once
#include "TrackerPolicy.h"
#include <map>

typedef std::pair<Trackable*, float> MyPairType;
struct CompareSecond
{
    bool operator()(const MyPairType& left, const MyPairType& right) const
    {
        return left.second < right.second;
    }
};


class DistanceTrackerPolicy :
	public TrackerPolicy
{
public:
	//DistanceTrackerPolicy(void);
	~DistanceTrackerPolicy(void);
	std::vector<Trackable*> execute(std::vector<Rect> rois, std::vector<Trackable*> tracked);

protected:
	std::pair<Trackable*, float> getMin(std::map<Trackable*, float> mymap);
};


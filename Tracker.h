#pragma once
#include "observer.h"
#include "ObjectDetector.h"
#include "Trackable.h"
#include "TrackerPolicy.h"




class Tracker :
	public Observer, public Observable
{
public:
	Tracker(ObjectDetector* detector, TrackerPolicy* policy){detector_ = detector; 
															 detector_->attach(this);
															 policy_ = policy;};
	~Tracker(void);

	void update();
	Mat getResultsFrame(){return resFrame_;};

protected:
	ObjectDetector* detector_;
	std::vector<Trackable*> trackedObjs_;
	TrackerPolicy* policy_;

	void drawResults();
	void removeOldTracks();

	Mat resFrame_;
};


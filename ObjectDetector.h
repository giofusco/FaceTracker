#pragma once
#include "observable.h"
#include "VideoSource.h"
#include"opencv2\highgui\highgui.hpp"
#include <vector>

using namespace cv;

class ObjectDetector :
	public Observable, public Observer
{
public:
	ObjectDetector(void){showResults_ = false;};
	
	
	~ObjectDetector(void);
	
	
	void setShowResults(bool showResult){ showResults_=showResult;};
	void setWindowName(string winName){ winName_ = winName;};
	
	bool isShowingResult(){return showResults_;};

	virtual  void detect() = 0;
	
	void update(){ currFrame_ = videoSource_->getCurrentFrame(); detect(); if (showResults_) showResults();};
	void virtual showResults() = 0;
	
	Mat getResultsFrame(){return resFrame_;};
	Mat getCurrentFrame(){return currFrame_;};

	std::vector<Rect> getDetectionRois(){ return detectionRois_;};

protected:
	VideoSource* videoSource_; //video source
	std::string winName_;	//name of the window in which to show the result
	bool showResults_;
	Mat currFrame_;
	Mat resFrame_;
	std::vector<Rect> detectionRois_;
	

};


#pragma once

#include<vector>
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include<iostream>

using namespace cv;

class Trackable
{
public:
	
	Trackable(Rect roi);
	~Trackable(void);
	
	void setRoi(Rect roi){
		if ((observedFrames_ % 10) == 0)
			prevRoi_ = lastRoi_; 
		lastRoi_ = roi; 
		updated_ = true; 
		computeDirection();
		observedFrames_++;};
	float getDistance(Rect roi); //get the distance between last object position and current one
	bool isUpdated(){return updated_;};

	void updateStatus(){if (updated_){
						updated_ = false;
						droppedFrames_ = 0;
						}
						else{
							droppedFrames_++;
						}};
	
	int getDroppedFrames(){return droppedFrames_;};
	int getObservedFrames(){return observedFrames_;};
	long int getId(){return trackId_;};
	Rect getRoi(){return lastRoi_;};
	string getDirection(){return direction_;};

protected:
	
	Rect lastRoi_;
	Rect prevRoi_;
	int observedFrames_;
	bool updated_;
	float dist_;
	int droppedFrames_; // counts how many frames since last detection
	string direction_;
	void computeDirection();
	long int trackId_;
private:
	static long int id_;
	
};


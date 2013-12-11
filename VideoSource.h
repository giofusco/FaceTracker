#pragma once
#include "observable.h"
#include "opencv2\highgui\highgui.hpp"
#include<iostream>
using namespace cv;

class VideoSource :
	public Observable
{
public:
	
	VideoSource(void){videoSource_ = VideoCapture(0); isInit_ = initVideoSource();};
	VideoSource(int width, int height);
	VideoSource(VideoCapture vcap){videoSource_ = vcap; isInit_ = initVideoSource();};
	~VideoSource(void);
	
	void setVideoSource(VideoCapture vcap){ videoSource_ = vcap; initVideoSource();};
	Mat getFrame();

	double getFPS(){ return videoSource_.get(CV_CAP_PROP_FPS); };
	Mat getCurrentFrame(){return currentFrame_;};
	Mat getPreviousFrame(){return previousFrame_;};
	
private:
	VideoCapture videoSource_;
	bool isInit_;
	bool initVideoSource();
	Mat currentFrame_;
	Mat previousFrame_;

};


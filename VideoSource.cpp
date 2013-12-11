#include "VideoSource.h"


VideoSource::~VideoSource(void)
{
}

VideoSource::VideoSource(int width, int height){
	videoSource_ = VideoCapture(0); 
	isInit_ = initVideoSource();
	if (isInit_){
		videoSource_.set(CV_CAP_PROP_FRAME_WIDTH,width);
		videoSource_.set(CV_CAP_PROP_FRAME_HEIGHT,height);
	//	videoSource_.set(CV_CAP_PROP_FPS,30);
	}
}


bool VideoSource::initVideoSource(){
	previousFrame_ = NULL;
	currentFrame_ = NULL;
	if(!videoSource_.isOpened()) {
			return 0;
			std::cerr << "Error initializing video source" << std::endl;
		}
		else return 1;
}

Mat VideoSource::getFrame(){
	
	if (isInit_){
			previousFrame_ = currentFrame_;	
			videoSource_ >> currentFrame_;
			notify();
	}
	else std::cerr << "Video Source not initialized." << std::endl;

	return currentFrame_;
}
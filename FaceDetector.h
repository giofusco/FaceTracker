#pragma once
#include "objectdetector.h"
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
#include <opencv2/core/mat.hpp>
#include <opencv2\core\operations.hpp>
#include "opencv2/objdetect/objdetect.hpp"



class FaceDetector :
	public ObjectDetector
{
public:
	
	FaceDetector(VideoSource* vsrc){
		videoSource_ = vsrc;
		vsrc->attach(this);
		showResult_ = false;
		cascadeName_ = "haarcascade_frontalface_alt_tree.xml";
		if( !cascade_.load( cascadeName_) ){ std::cerr << "Face Detector: Error Loading Cascade" << std::endl; }; 
		detectEyes_ = false; };

	FaceDetector(VideoSource* vsrc, string cascadeName){
		videoSource_ = vsrc;
		vsrc->attach(this);
		showResult_ = false;
		cascadeName_ = cascadeName;
		if( !cascade_.load( cascadeName_) ){ std::cerr << "Face Detector: Error Loading Cascade" << std::endl; }; 
		detectEyes_ = false; };


	~FaceDetector(void);
	void showResults();
	void detect();
	void enableEyesDetection(bool enable){detectEyes_ = enable;};
	void setCascadeName(string cascadeName){cascadeName_ = cascadeName;};
	string getCascadeName(){return cascadeName_;};

private:
	string cascadeName_;
	CascadeClassifier cascade_;
	bool detectEyes_;
};


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
		showResults_ = false;
		faceCascadeName_ = "haarcascade_frontalface_alt_tree.xml";
		if( !faceCascade_.load( faceCascadeName_ ) ){ std::cerr << "Face Detector: Error Loading Cascade" << std::endl; }; 
		detectEyes_ = false; };

	FaceDetector(VideoSource* vsrc, string faceCascadeName){
		videoSource_ = vsrc;
		vsrc->attach(this);
		showResults_ = false;
		faceCascadeName_ = faceCascadeName;
		if( !faceCascade_.load( faceCascadeName_) ){ std::cerr << "Face Detector: Error Loading Cascade" << std::endl; }; 
		detectEyes_ = false; };

	FaceDetector(VideoSource* vsrc, string faceCascadeName, string eyesCascadeName){
		videoSource_ = vsrc;
		vsrc->attach(this);
		showResults_ = false;
		faceCascadeName_ = faceCascadeName;
		eyesCascadeName_ = eyesCascadeName;
		if( !faceCascade_.load( faceCascadeName_) ){ std::cerr << "Face Detector: Error Loading Cascade" << std::endl; }; 
		detectEyes_ = true; 
		if( !eyesCascade_.load( eyesCascadeName_) ){ std::cerr << "Eyes Detector: Error Loading Cascade" << std::endl; }; };


	~FaceDetector(void);
	void showResults();
	void detect();
	void enableEyesDetection(bool enable){detectEyes_ = enable;};
	void setFaceCascadeName(string cascadeName){faceCascadeName_  = cascadeName;};
	void setEyesCascadeName(string cascadeName){eyesCascadeName_  = cascadeName;};
	string getCascadeName(){return faceCascadeName_ ;};

private:
	string faceCascadeName_ ;
	string eyesCascadeName_ ;
	CascadeClassifier faceCascade_;
	CascadeClassifier eyesCascade_;
	std::vector< std::vector<Rect> > eyesRois_;

	bool detectEyes_;
};


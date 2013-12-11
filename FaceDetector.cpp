#include "FaceDetector.h"


FaceDetector::~FaceDetector(void)
{
}

void FaceDetector::detect(){

	Mat grayFrame;
	cvtColor(currFrame_,grayFrame,CV_BGR2GRAY);
	
	//TODO:
	//set image subregion in which perform detection if detectionRois_ is not empty.
	// If no detection occurrs after N frames, consider the whole image.
	// Does it make sense if camera moves?

	//TODO2: bring outside the detector parameters
	//if (! detectionRois_.size() == 0)
		//detectionRois_.clear();
	cascade_.detectMultiScale(grayFrame, detectionRois_, 1.1, 2, 0, Size(70, 70) );

	
	if (detectEyes_){
		// TODO refine rois using eyes detection -- what about sunglasses?
		;
       }

	notify();

}

void FaceDetector::showResults(){
	for( std::vector<Rect>::iterator it = detectionRois_.begin(); it < detectionRois_.end(); ++it )
    {
      Mat faceROI = currFrame_( *it );
	  resFrame_ = currFrame_;
	   //-- Draw the face
      Point center( (*it).x + (*it).width*0.5, (*it).y + (*it).height*0.5 );
      ellipse( resFrame_, center, Size( (*it).width*0.5, (*it).height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );

	}
}
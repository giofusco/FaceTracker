#include "FaceDetector.h"


FaceDetector::~FaceDetector(void)
{
}

void FaceDetector::detect(){

	Mat grayFrame;
	cvtColor(currFrame_,grayFrame,CV_BGR2GRAY);
	
	faceCascade_.detectMultiScale(grayFrame, detectionRois_, 1.1, 2, 0, Size(70, 70) );

	
	if (detectEyes_){
		std::vector<Rect> tmpRois;
		for( std::vector<Rect>::iterator it = detectionRois_.begin(); it < detectionRois_.end(); ++it ){
			std::vector<Rect> eyes;
			eyesCascade_.detectMultiScale( grayFrame(*it), eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
			if (eyes.size() > 0){
				eyesRois_.push_back(eyes);
				tmpRois.push_back(*it);
			}
		}
		detectionRois_ = tmpRois;
		
       }

	if (showResults_)
		showResults();

	notify();

}

void FaceDetector::showResults(){
	if (!detectEyes_){
		for( std::vector<Rect>::iterator it = detectionRois_.begin(); it < detectionRois_.end(); ++it )
		{
		  Mat faceROI = currFrame_( *it );
		  //resFrame_ = currFrame_;
		   //-- Draw the face
		  Point center( (*it).x + (*it).width*0.5, (*it).y + (*it).height*0.5 );
		  ellipse( currFrame_, center, Size( (*it).width*0.5, (*it).height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );

		}
	}
	else{
		std::vector<Rect>::iterator it;
		std::vector< std::vector<Rect> >::iterator it2;
		for( it = detectionRois_.begin(),  it2 = eyesRois_.begin(); it < detectionRois_.end() && 
			it2 < eyesRois_.end(); ++it, ++it2 )
		{
		  Mat faceROI = currFrame_( *it );
		  //resFrame_ = currFrame_;
		   //-- Draw the face
		  Point center( (*it).x + (*it).width*0.5, (*it).y + (*it).height*0.5 );
		  ellipse( currFrame_, center, Size( (*it).width*0.5, (*it).height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
		  std::vector<Rect>::iterator it3;
		  for (it3 = it2->begin(); it3 < it2->end(); ++it3){
			Point center( (*it).x + (*it3).x + (*it3).width*0.5, (*it).y + (*it3).y + (*it3).height*0.5 );
			int radius = cvRound( ((*it3).width + (*it3).height)*0.25 );
			circle( currFrame_, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
		  }

		}

	}
}
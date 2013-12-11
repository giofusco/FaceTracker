#include <stdio.h>
#include <stdlib.h>
#include "VideoSource.h"
#include<time.h>
#include"FaceDetector.h"
#include "Tracker.h"
#include "DistanceTrackerPolicy.h"
int main(int argc, char* argv[]){

	
	VideoSource* vsrc  = new VideoSource();

	FaceDetector* faceDet = new FaceDetector(vsrc);
	//faceDet->setShowResults(1);
	TrackerPolicy* policy = new DistanceTrackerPolicy();	
	Tracker* tracker = new Tracker(faceDet, policy);


	Mat frame;
	time_t start,end;
	double sec, fps;
	
	
	namedWindow("Input Source");
	time(&start);
	int counter=0;	
	Mat resFrame;
	for (;;) {
		
		// extract the frame 
		frame = vsrc->getFrame();
		
		//do something with it

		//compute FPS
		time(&end);
		++counter;
		sec=difftime(end,start);
		fps=counter/sec;
		//write over image
		
		putText(frame, string("FPS: " + std::to_string(fps)), cvPoint(30,30), 
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,255,0), 1, CV_AA);
		
		//show frame
		if (tracker->getResultsFrame().data != 0)
			imshow("Input Source", tracker->getResultsFrame());
		else imshow("Input Source", frame);
		//imshow("Input Source", frame);
		
			
		if(waitKey(30) >= 0) break;
	}


	return 0;
}
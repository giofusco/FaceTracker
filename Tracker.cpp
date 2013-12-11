#include "Tracker.h"


Tracker::~Tracker(void)
{
}



void Tracker::update(){

	//TODO: too many responsabilities, the association method could become a strategy pattern

	std::vector<Rect> rois = detector_->getDetectionRois();
	trackedObjs_ = policy_->execute(rois, trackedObjs_);
	

	//update trackable status
	for (std::vector<Trackable*>::iterator it = trackedObjs_.begin(); it != trackedObjs_.end(); ++it)
		(*it)->updateStatus();

	removeOldTracks();
	drawResults();

	//}
}

void Tracker::removeOldTracks(){

	//remove old trackings (not seen in N frames)
	std::vector<Trackable*>::iterator it = trackedObjs_.begin();

   
	trackedObjs_.erase(std::remove_if(trackedObjs_.begin(), trackedObjs_.end(), [](Trackable* track)
	{
    return track->getDroppedFrames() > 30;
	}), trackedObjs_.end());

	
}



void Tracker::drawResults(){

	//draw on the frame
	resFrame_ = detector_->getCurrentFrame();

	for (std::vector<Trackable*>::iterator it = trackedObjs_.begin(); it != trackedObjs_.end(); ++it)
    {
      //draw only when visible
		if ( (*it)->getDroppedFrames() == 0 && (*it)->getObservedFrames()>5){
			Rect roi = (*it)->getRoi();
			long int id = (*it)->getId();
			//-- Draw the face

			//check boundaries
			Point p1(roi.x, roi.y);
			int x = roi.x + roi.width;
			if (x > resFrame_.cols)
				x = resFrame_.cols;

			int y = roi.y + roi.height;
			if (y > resFrame_.rows)
				y = resFrame_.rows;

			Point p2(roi.x, roi.y);
			Point center( roi.x + roi.width*0.5, roi.y + roi.height*0.5 );
			rectangle(resFrame_, p1, Point(x,y), Scalar(255,0,0),1);
			//ellipse( resFrame_, center, Size( roi.width*0.5, roi.height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
			putText(resFrame_, string("Track #: " + std::to_string(id)), p2, 
				FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,255,0), 1, CV_AA); 
			putText(resFrame_, (*it)->getDirection(), center, 
				FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,255,0), 1, CV_AA);
		}

	}


}


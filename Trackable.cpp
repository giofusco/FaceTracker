#include "Trackable.h"


long int Trackable::id_ = 0;

Trackable::~Trackable(void)
{
}

Trackable::Trackable(Rect roi){
	Trackable::id_++; 
	trackId_ =Trackable::id_; 
	observedFrames_ = 0 ; 
	lastRoi_=roi;
	droppedFrames_=0; 
	updated_=true;
	std::cout << "New track, id: " << this->id_ << std::endl;
};

float Trackable::getDistance(Rect roi){

	//compute roi center
	int x1 = (.5*roi.width + roi.x);
	int y1 = (roi.height + roi.x)/2;

	Point center1( roi.x + roi.width*0.5, roi.y + roi.height*0.5 );
	Point center2( lastRoi_.x + lastRoi_.width*0.5, lastRoi_.y + lastRoi_.height*0.5 );

	dist_ = sqrt(pow(center1.x-center2.x,2) + pow(center1.y-center2.y,2));
	return dist_;
		
}

void Trackable::computeDirection(){

	//compute roi area delta
	if (prevRoi_.area() != 0) {
	float delta = (float)(1. * lastRoi_.area()) / (float)((1. * prevRoi_.area()));
	//std::cout << "Area ratio " << delta << std::endl;
	if (delta < .8)
		direction_ = "-";
	else if (delta > 1.25)
		direction_ = "+";
	else direction_ =".";
	}
	else direction_ ="*";
}
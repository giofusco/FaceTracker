#include "DistanceTrackerPolicy.h"

DistanceTrackerPolicy::~DistanceTrackerPolicy(void)
{
}


std::pair<Trackable*, float> DistanceTrackerPolicy::getMin(std::map<Trackable*, float> mymap) 
{
  std::pair<Trackable*, float> min 
      = *min_element(mymap.begin(), mymap.end(), CompareSecond());
  return min; 
}

std::vector<Trackable*> DistanceTrackerPolicy::execute(std::vector<Rect> rois, std::vector<Trackable*> tracked){

	//	if (rois.size()>0){
	// each detected roi is a trackable, no need to associate 
	if (tracked.size() == 0){
		for (std::vector<Rect>::iterator rIt = rois.begin(); rIt!= rois.end(); ++rIt){
			tracked.push_back(new Trackable((*rIt)));
		}
	}

	else{
				
		std::vector<Trackable*> tmpObjs;
		for (std::vector<Rect>::iterator rIt = rois.begin(); rIt!= rois.end(); ++rIt){
			std::map<Trackable*,float> distances;
		
			for (std::vector<Trackable*>::iterator it = tracked.begin(); it != tracked.end(); ++it){
				// compute distance and take min
				if (! (*it)->isUpdated()){ //avoid computing over already updated tracked objects 
					distances.insert( std::pair<Trackable*,float>( (*it), (*it)->getDistance(*rIt)));
					//std::cout << (*it)->getDistance(*rIt) << std::endl;
				}

			}
			
			if (! distances.size()  == 0){
				std::pair<Trackable*,float> closestPair = getMin(distances);
				Trackable* closest = closestPair.first;
				float distance = closestPair.second;
				// threshold based on roi size. The camera is moving, can we make assumptions/exploit motion vector?
				float maxDist = .5*(closest->getRoi().width);
				
				if (distance < maxDist){
					closest->setRoi((*rIt));
				}
				else //it is a new tracked object
					//trackedObjs_.push_back(new Trackable((*rIt)));
					tmpObjs.push_back(new Trackable((*rIt)));
			}
		}
		//put new trackable in the tracked list
		for (std::vector<Trackable*>::iterator it = tmpObjs.begin(); it != tmpObjs.end(); ++it)
			tracked.push_back((*it));
	}
	return tracked;
}

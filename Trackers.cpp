#include "Trackers.h"

CoordHitTracker::CoordHitTracker(Coord c) {
    this->coord = c;
    this->hit = false;
}

CoordHitTracker::CoordHitTracker(const CoordHitTracker& C) {
	this->coord = Coord{ C.coord.row, C.coord.col };
	this->hit = C.hit;
}

bool CoordHitTracker::isHit() {
    return(this->hit);
}

bool CoordHitTracker::attemptHit(Coord c) {
    if((c == this->coord) && (this->hit == false)) {
        this->hit = true;
        return true;
    }
    return false;
}

Coord CoordHitTracker::getCoord() {
    return coord;
}

ShipTracker::ShipTracker(std::vector<CoordHitTracker*> coordPtrVec) {
	for (int i = 0; i < coordPtrVec.size(); i++) {
		this->coordTrackers.push_back(coordPtrVec.at(i));
	}
	length = this->coordTrackers.size();
	this->hitNum = 0;
}

ShipTracker::ShipTracker(const ShipTracker& otherShip) {
	for (int i = 0; i < otherShip.length; i++) {
		this->coordTrackers.push_back(otherShip.coordTrackers.at(i));
		this->length = otherShip.length;
		this->hitNum = otherShip.hitNum;
	}
}

ShipTracker::~ShipTracker() {
	for (int i = 0; i < this->length; i++) {
		delete this->coordTrackers.at(i);
	}
}

bool ShipTracker::attemptHit(Coord c) {
    for(int i = 0; i < this->length; i++) {
        if(this->coordTrackers.at(i)->attemptHit(c)) {
            this->hitNum++;
            return true;
        } 
    }
    return false;
}

bool ShipTracker::isSunk() {
    return(this->hitNum >= this->length);
}

int ShipTracker::getLength() {
    return this->length;
}

FleetTracker::FleetTracker(std::vector<ShipTracker*>* trackerPtr) {
	this->shipTrackersPtr = trackerPtr;
	this->size = shipTrackersPtr->size();
	this->sunkNum = 0;
	this->lastGuessSunkLength = 0;
	this->lastGuessHit = false;
}

FleetTracker::~FleetTracker() {
	for (int i = 0; i < this->shipTrackersPtr->size(); i++) {
		for (int j = 0; j < this->shipTrackersPtr->at(i)->getLength(); j++) {
			delete this->shipTrackersPtr->at(j);
		}
	}
}

bool FleetTracker::attemptHit(Coord c) {
    for(int i = 0; i < this->size; i++) {
        if(this->shipTrackersPtr->at(i)->attemptHit(c)) {
            this->lastGuessHit = true;
            this->lastCoordHit = c;
            if(this->shipTrackersPtr->at(i)->isSunk()) {
                this->lastGuessSunkLength = this->shipTrackersPtr->at(i)->getLength();
                this->sunkNum++;
            }   
            return true;
        } else {
            this->lastGuessHit = false;
            this->lastGuessSunkLength = 0;
        }
    }
    return false;
}

bool FleetTracker::sunkOnLastGuess() {
    return(this->lastGuessSunkLength > 0);
}

int FleetTracker::sunkLengthOnLastGuess() {
    return this->lastGuessSunkLength;
}

bool FleetTracker::hitOnLastGuess() {
    return(this->lastGuessHit);
}

bool FleetTracker::isFleetSunk() {
    return(this->sunkNum >= this->size);
}

Coord FleetTracker::getLastCoordHit() {
    return(this->lastCoordHit);
}
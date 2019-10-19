#include "Trackers.h"

CoordHitTracker::CoordHitTracker(Coord c) {
    this->coord = c;
    this->hit = false;
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

ShipTracker::ShipTracker(std::vector<CoordHitTracker*>* coordHitVectPtr) {
    this->coordTrackersPtr = coordHitVectPtr;
    this->length = this->coordTrackersPtr->size();
    this->hitNum = 0;
}

ShipTracker::~ShipTracker() {
    if(this->coordTrackersPtr != nullptr) delete this->coordTrackersPtr;
}

bool ShipTracker::attemptHit(Coord c) {
    for(int i = 0; i < this->length; i++) {
        if(this->coordTrackersPtr->at(i)->attemptHit(c)) {
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

FleetTracker::FleetTracker(std::vector<ShipTracker*>* trackerPtrsVect) {
    this->shipTrackersPtrsPtr = trackerPtrsVect;
    this->size = this->shipTrackersPtrsPtr->size();
    this->sunkNum = 0;
    this->lastGuessHit = false;
    this->lastGuessSunkLength = 0;
}

FleetTracker::~FleetTracker() {
    if(this->shipTrackersPtrsPtr != nullptr) delete this->shipTrackersPtrsPtr;
}

bool FleetTracker::attemptHit(Coord c) {
    for(int i = 0; i < this->size; i++) {
        if(this->shipTrackersPtrsPtr->at(i)->attemptHit(c)) {
            this->lastGuessHit = true;
            this->lastCoordHit = c;
            if(this->shipTrackersPtrsPtr->at(i)->isSunk()) {
                this->lastGuessSunkLength = this->shipTrackersPtrsPtr->at(i)->getLength();
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
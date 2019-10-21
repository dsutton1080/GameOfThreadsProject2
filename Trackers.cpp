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

ShipTracker::ShipTracker() {
	this->length = 0;
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
}

bool ShipTracker::attemptHit(Coord c) {
    for(int i = 0; i < this->length; i++) {
        if(this->coordTrackers.at(i).attemptHit(c)) {
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

void ShipTracker::appendCoordTracker(const CoordHitTracker& cht) {
    CoordHitTracker tmp = cht;
    this->coordTrackers.push_back(tmp);
    this->length++;
}

FleetTracker::FleetTracker() {
	this->size = 0;
	this->sunkNum = 0;
	this->lastGuessSunkLength = 0;
	this->lastGuessHit = false;
    this->lastHitSunk = true;
}

FleetTracker::~FleetTracker() {
}

bool FleetTracker::attemptHit(Coord c) {
    for(int i = 0; i < this->size; i++) {
        if(this->shipTrackers.at(i).attemptHit(c)) {
            this->lastGuessHit = true;
            this->lastCoordHit = c;
            if(this->shipTrackers.at(i).isSunk()) {
                this->lastGuessSunkLength = this->shipTrackers.at(i).getLength();
                this->lastHitSunk = true;
                this->sunkNum++;
            }   
            else {
                this->lastHitSunk = false;
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

bool FleetTracker::sunkOnLastHit() {
    return this->lastHitSunk;
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

void FleetTracker::appendShipTracker(const ShipTracker& st) {
    ShipTracker tmp = st;
    this->shipTrackers.push_back(tmp);
    this->size++;
}
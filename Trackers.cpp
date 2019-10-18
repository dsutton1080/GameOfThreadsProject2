#include "Trackers.h"

CoordHitTracker::CoordHitTracker(Coord c) {
    this->coord = c;
    this->hit = false;
}

bool CoordHitTracker::isHit() {
    return(this->hit);
}

bool CoordHitTracker::attemptHit(Coord c) {
    if(c == this->coord) {
        this->hit = true;
        return true;
    }
    return false;
}

Coord CoordHitTracker::getCoord() {
    return coord;
}



ShipTracker::ShipTracker(Coord* coordArr, int size) {
    // this->coordTrackers = CoordHitTracker(Coord {0, 0})[size];
}
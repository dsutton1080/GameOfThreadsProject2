#ifndef TRACKERS_H
#define TRACKERS_H

#include "Utils.cpp"

class CoordHitTracker {
    private:
        Coord coord;
        bool hit;
    public:
        CoordHitTracker();
        bool isHit();
        bool attemptHit(Coord c);
        Coord getCoord();
};

class ShipTracker {
    private:
        CoordHitTracker* coordTrackers;
        int length;
        int hitNum;
        bool sunk;
    public:
        ShipTracker(int size);
        ~ShipTracker();
        bool attemptHit(Coord c);
        bool isSunk();
};

class FleetTracker {
    
}


#endif
#ifndef TRACKERS_H
#define TRACKERS_H

#include "Utils.cpp"

class CoordHitTracker {
    private:
        Coord coord;
        bool hit;
    public:
        CoordHitTracker(Coord c);
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
        ShipTracker(Coord* coordArr, int size);
        ~ShipTracker();
        bool attemptHit(Coord c);
        bool isSunk();
};

class FleetTracker {
    private:
        ShipTracker* shipTrackers;
        int size;
        int sunkNum;
        int sunkLastGuess;
        bool allSunk;
        bool lastGuessHit;
    public:
        FleetTracker(int size);
        ~FleetTracker();
        bool attemptHit(Coord c);
        int sunkOnLastGuess();
        bool isFleetSunk();
        bool hitOnLastGuess();
};


#endif
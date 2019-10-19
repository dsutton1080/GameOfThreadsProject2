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
        std::vector<CoordHitTracker>* coordTrackersPtr;
        int length;
        int hitNum;
    public:
        ShipTracker(std::vector<CoordHitTracker>* coordHitVectPtr);
        ~ShipTracker();
        bool attemptHit(Coord c);
        bool isSunk();
        int getLength();
};

class FleetTracker {
    private:
        std::vector<ShipTracker*>* shipTrackersPtrsPtr;
        int size;
        int sunkNum;
        int lastGuessSunkLength;
        bool lastGuessHit;
    public:
        FleetTracker(std::vector<ShipTracker*>* trackerPtr);
        ~FleetTracker();
        bool attemptHit(Coord c);
        bool sunkOnLastGuess();
        int sunkLengthOnLastGuess();
        bool isFleetSunk();
        bool hitOnLastGuess();
};


#endif
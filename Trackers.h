#ifndef TRACKERS_H
#define TRACKERS_H

#include "Utils.h"

class CoordHitTracker {
    private:
        Coord coord;
        bool hit;
    public:
        CoordHitTracker(Coord c);
		CoordHitTracker(const CoordHitTracker& C);
        bool isHit();
        bool attemptHit(Coord c);
        Coord getCoord();
};

class ShipTracker {
    private:
        std::vector<CoordHitTracker*> coordTrackers;
        int length;
        int hitNum;
    public:
        ShipTracker(std::vector<CoordHitTracker*> coordPtrVect);
		ShipTracker(const ShipTracker& otherShip);
        ~ShipTracker();
        bool attemptHit(Coord c);
        bool isSunk();
        int getLength();
};

class FleetTracker {
    private:
		std::vector<ShipTracker*>* shipTrackersPtr;
        int size;
        int sunkNum;
        int lastGuessSunkLength;
        bool lastGuessHit;
        bool lastHitSunk;
        Coord lastCoordHit;
    public:
        FleetTracker(std::vector<ShipTracker*>* trackerPtr);
        ~FleetTracker();
        bool attemptHit(Coord c);
        bool sunkOnLastGuess();
        bool sunkOnLastHit();
        int sunkLengthOnLastGuess();
        bool isFleetSunk();
        bool hitOnLastGuess();
        Coord getLastCoordHit();
};


#endif
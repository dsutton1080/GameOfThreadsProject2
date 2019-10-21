#ifndef TRACKERS_H
#define TRACKERS_H

#include "Utils.h"

class CoordHitTracker {
    private:
        //
        Coord coord;
        //
        bool hit;
    public:
        /**
        *@param c: The coordinate to be tracked
        *@pre c is a valid coordinate
        *@post A CoordHitTracker is created for the given coordinate
        */
        CoordHitTracker(Coord c);

        /**
        *@brief Copy constructor for CoordHitTracker object
        */
		CoordHitTracker(const CoordHitTracker& C);

        /**
        *@brief returns true if the coordinate in the tracker has been hit
        */
        bool isHit();

        /**
        *@param c: A coordinate that is being guessed
        *@pre c is a valid coordinate
        *@return returns true if the guess matches the trackers coordinate
        */
        bool attemptHit(Coord c);

        /**
        *@pre none The coordinate being tracked
        *@return
        */
        Coord getCoord();
};

class ShipTracker {
    private:
        //A list of CoordHitTrackers
        std::vector<CoordHitTracker> coordTrackers;
        //The length of the tracker lsit
        int length;
        //The number of coords being tracked that have been hit
        int hitNum;
    public:
        /**
        *@pre none
        *@post An empty ship tracker object is created
        */
        ShipTracker();
        /**
        *@brief Copy constructor for the ship tracker object
        */
		ShipTracker(const ShipTracker& otherShip);
        /**
        *@brief Destructor for the ship tracker object
        */
        ~ShipTracker();
        /**
        *@param c: A coordinate to be guessed
        *@pre c is a valid coordinate
        *@return True if the guess hits one of the coords being tracked
        */
        bool attemptHit(Coord c);
        /**
        *@pre none
        *@return True if all the tracked coordinates have been hit
        */
        bool isSunk();
        /**
        *@pre none
        *@return The length of the ship being tracked
        */
        int getLength();
        /**
        *@param cht: A coordinate tracker object
        *@pre none
        *@post The coordinate specified is added to the ship tracker
        */
        void appendCoordTracker(const CoordHitTracker& cht);
};

class FleetTracker {
    private:
        //
		std::vector<ShipTracker> shipTrackers;
        //
        int size;
        //
        int sunkNum;
        //
        int lastGuessSunkLength;
        //
        bool lastGuessHit;
        //
        bool lastHitSunk;
        //
        Coord lastCoordHit;
    public:
        /**
        *@pre none
        *@post An empty fleet tracker is created
        */
        FleetTracker();
        /**
        *@brief Destructor of the fleet tracker object
        */
        ~FleetTracker();
        /**
        *@param c: The coordinate being guessed
        *@pre c is a valid coordinate
        *@return True if the given coord hits one of the ships in the fleet
        */
        bool attemptHit(Coord c);
        /**
        *@return True if the last guess against the fleet sunk a ship
        */
        bool sunkOnLastGuess();
        /**
        *@return True if the last time the fleet was hit a ship sunk
        */
        bool sunkOnLastHit();
        /**
        *@return The length at the last ship that was sunk
        */
        int sunkLengthOnLastGuess();
        /**
        *@return True if all the ships in the fleet have been sunk
        */
        bool isFleetSunk();
        /**
        *@return True if the last guess hit a ship in the fleet
        */
        bool hitOnLastGuess();
        /**
        *@pre The fleet has been hit at least once
        *@return The last coordinate that hit a ship in the fleet
        */
        Coord getLastCoordHit();
        /**
        *@param st: A ship tracker object
        *@pre none
        *@post The given ship is added to the fleet
        */
        void appendShipTracker(const ShipTracker& st);
};


#endif
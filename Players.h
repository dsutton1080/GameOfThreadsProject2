#ifndef PLAYERS_H
#define PLAYERS_H

#include "Boards.h"
#include "Trackers.h"

class Players{
protected:
	///Creating an object to access to board class
	Boards myBoard;
	///String that save player's desire name
	std::string ID;
	// 
	FleetTracker fleetTracker;
	///row number for hitting ships
	int row;
	///col char for hitting ships
	char column;
	///bool that to determine whether players are ready to play
	bool allSet;
public:
	/************************************
	 * Constructor/Deconstructor
	 ***********************************/
	 /**
	  *@brief creates the player, which has access to their boards.
	  */
 	Players();
	/**
	 *@brief Frees up any assests the player has from memory.
	 */
	~Players();
	/************************************
	 * Get/Set Functions
	 ***********************************/
	 /**
	  *@pre None.
	  *@brief Grabs both boards to display.
	  */
	void getBoards() const;
	/**
	 *@brief Displays the board from an offensive standpoint.
	 */
	void getOffensiveBoard() const;
	/**
	 *@brief Displays the board from a defensive standpoint.
	 */
	void getDefensiveBoard() const;
	/**
	 *@brief Gets which column the user wants the ship in.
	 */
	char getColumn();
	/**
	 *@brief Gets which row the user wants the ship in.
	 */
	int getRow();
	/**
	 *@pre Number of ships being placed known.
	 *@post All ships are placed on the board.
	 */
	virtual void setShips(int);
	/**
	 *@pre Name desired for the player is given in exec.
	 *@post Name is placed in storage for use by Players.
	 */
	void setID(std::string);
	/**
	 *@brief Returns the player name to the called function.
	 */
	std::string getID();
	/**
	 *@pre Ships are placed on the board.
	 *@post Returns true if a ship is at that location.
	 */
	bool getHit(char, int);
	/**
	 *@brief IO interaction to set the player's name
	 */
	virtual void setIDinteractive();

	/************************************
	 * Functions
	 ***********************************/

	/**
	 *@pre None.
	 *@brief If all ships are set, return true.
	 */
    bool shipsSet();
	/**
	 *@brief If the player has no more ships, return true.
	 */
	bool hasLost();
	/**
	 *@brief Marks my board with hits.
	 */
	void markMyHits(char, int);
	/**
	 *@brief Marks my board with misses.
	 */
	void markMyMisses(char, int);
	/**
	 *@brief Marks the opponent's board with hits.
	 */
	void markTheirHits(char, int);
	/**
	 *@brief Marks the opponent's board with misses.
	 */
	void markTheirMisses(char, int);
	/**
	 *@pre Game is finished, and another is wanting to begin.
	 *@post Board is cleaned off.
	 */
	void cleanBoard();
    /**
    *@pre none
    *@return true if the player is an AI, false otherwise
    */
	virtual bool isAI();
    /**
     *@brief returns a bool indicating whether this player was hit on the last shot.
    */
	bool wasHitPrev();

    /**
     *@brief returns an int 1-5 (or 0) indicating the size of the last sunk ship
    */
	int prevSunkLength();

    /**
    *@brief Returns true the last guess against the player's board sunk a ship
    */
	bool wasSunkPrev();

    /**
    *@brief Returns true if the last time the player's board was hit a ship sunk
    */
    bool wasSunkPrevHit();

    /**
    *@brief updates the fleet tracker by giving it a guess Coord
    */
	void trackShot(Coord c);

    /**
    *@pre Player was hit at least once
    *@return The coordinate on which the player was last hit
    */
	Coord getLastHitCoord(); 

    /**
    *@pre none
    *@return The coordinate the user is prompted for
    */
	virtual Coord takeTurn();

    /**
    *@return The coordinate the user is prompted for
    */
	virtual Coord takeSpecialShot();

    /**
    *@brief Prints the result of a guess
    */
	virtual void guessFeedbackSignal();

    /**
    *@param c: A coordinate
    *@pre none
    *@returns True if the player has guessed that coordinate before, false otherwise
    */
	bool hasGuessedCoord(Coord c);

    /**
    *@param row: An int
    *@param col: An int
    *@pre Both parameters are in the range 0-7
    *@return The value of the player's defensivee board at the the coordinate specified
    */
	char getLocationChar(int row, int col);

};
#endif

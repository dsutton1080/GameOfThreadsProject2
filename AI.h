#ifndef AI_H
#define AI_H

#include "Players.h"

class AI : public Players {
private:
    //An integer that encodes the difficulty of the AI
    //1 for easy, 2 for medium, 3 for hard
	int difficulty;
    //The player the AI is playing against
	Players* otherPlayer;
    //Keeps track of whether the AI's last hit sunk a ship
	bool lastHitSunkShip;
    //Keeps track of whether the AI's last guess was a hit
	bool lastGuessWasHit;
    //Keeps track of whether the AI has tried guessing to the left and right
    //of the last coordinate it hit
	bool horizChecked;
    //How far away the next guess should be from firstHitOnShip (medium difficulty only)
	int offset;
    //Keeps track of whether the AI is guessing in a negative or positive direction
    //from firstHitOnShip (medium difficulty only)
	int offsetSign;
    //The coordinate of the first hit the AI got on the ship it is 
    //currently trying to sink (medium difficulty only)
	Coord firstHitOnShip;

public:
    /**
    *@param difficulty: Int encoding the difficulty of the AI
    *@param otherPlayerPtr: A pointer to the AI's opponent
    *@pre none
    *@post An AI created with the given difficulty setting and opponent
    */
	AI(int difficulty, Players* otherPlayerPtr);
    /**
    *@param The number of ships the AI is to set
    *@pre The AI has not already set its ships
    *@post All of the AIs ships are set
    */
	void setShips(int);

    /**
    *@brief returns true
    */
	bool isAI();

	/*
	- Invoked when its the AI's turn
	- Returns a 'Coord' struct containing the "row" and "col" properties (both of type int)
	- The returned Coord object should have both row, col in the range 0-7
	- The hard guess will need to have access to the other player's data to know where the
	ships are. This is why it has a pointer to the other player
	- Might be useful to create a generalized 'randomCoord()' function in Utils to provide
	a random Coord object, useful in any of the other methods using the combination of a
	randomly-generated row and column.
	- See 'Utils.cpp' file for the Coord struct definition
	*/

    /**
    *@brief Random every guess. Ensure that you don't guess what's already been guessed.
    */ 
	Coord easyGuess();

    /**
    *@brief Guesses randomly until it hits a ship, then keeps guessing nearby until it sinks it
    */
	Coord mediumGuess();

    /**
    *@brief Guesses knowing where all the opponents ships are
    */
	Coord hardGuess();

    /**
    *@brief Returns the guess that should be generated based on the AI's difficulty
    */
	Coord takeTurn();

    /**
    *@brief Returns the coordinate the user was prompted for their special shot
    */
	Coord takeSpecialShot();

    /**
    *@brief Prints the result of the AI's guess
    */
	void guessFeedbackSignal();
};
#endif
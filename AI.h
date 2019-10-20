#ifndef AI_H
#define AI_H

#include "Players.h"

class AI : public Players {
private:
	int difficulty;
	Players* otherPlayer;
	/*---------------------------------------
	The following are variables used for
	mediumGuess() method
	----------------------------------------*/
	bool lastHitSunkShip;
	bool lastGuessWasHit;
	bool horizChecked;;
	int offset;
	int offsetSign;
	Coord firstHitOnShip;
	//----------------------------------------

public:
	AI(int difficulty, Players* otherPlayerPtr);
    ~AI();
	void setShips(int);
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

	// Random every guess. Ensure that you don't guess what's already been guessed.
	Coord easyGuess();


	Coord mediumGuess();

	// Must use the pointer to the other player to know where the other player's ships are.
	// Be sure to keep straight which spots on the other player's have already been guessed 
	Coord hardGuess();

	// returns the Coord to be guessed based on the AI difficulty
	Coord takeTurn();

	Coord takeSpecialShot();

	void guessFeedbackSignal();
};
#endif
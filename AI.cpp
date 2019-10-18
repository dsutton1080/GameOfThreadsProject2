#include "AI.h"
#include <stdlib.h>
#include <time.h>

AI::AI(int difficulty) : Players() {
	srand(time(NULL));
	this->difficulty = difficulty;

	//Initialize variables needed for medium difficulty
	//-------------------------------------------------
	this->lastHitSunkShip = true; //Initiallzed to true to on medium
								  //the AI will start by guessing randomly
	this->lastGuessWasHit = false;
	//-------------------------------------------------
}	

void AI::setShips(int numShips) {
	int row, col; 
	char directions[] = { 'u', 'd', 'l', 'r' }; 
	char dir;
	int size = numShips;
	int* markedCols = new int[size];
	int* markedRows = new int[size];
	int count = 0;

	for (int size = numShips; size > 0; size--) {
		row = rand() % 8;
		col = rand() % 8;
		dir = directions[rand() % 4];

		while (count < size) {
			markedCols[count] = col;
			markedRows[count] = row;
			if (count == 0) {
				if (myBoard->isValid(col, row)) {
					myBoard->markShips(col, row);
					count++;
				}
				else {
					row = rand() % 8;
					col = rand() % 8;
				}
			}
			else {
				if (dir == 'u' && myBoard->isValid(col, row - 1)) {
					myBoard->markShips(col, row - 1);
					row--;
					count++;
				}
				else if (dir == 'd' && myBoard->isValid(col, row + 1)) {
					myBoard->markShips(col, row + 1);
					row++;
					count++;
				}
				else if (dir == 'l' && myBoard->isValid(col - 1, row)) {
					myBoard->markShips(col - 1, row);
					col--;
					count++;
				}
				else if (dir == 'r' && myBoard->isValid(col + 1, row)) {
					myBoard->markShips(col + 1, row);
					col++;
					count++;
				}
				else {
					for (int i = 0; i <= count; i++) {
						myBoard->unmarkShips(markedCols[i], markedRows[i]);
					}
					count = 0;
					row = rand() % 8;
					col = rand() % 8;
					dir = directions[rand() % 4];
				}
			}
		}
		count = 0;
	}
	delete[] markedCols;
	delete[] markedRows;

	this->allSet = true;
}

bool AI::isAI() {
	return true;
}

Coord AI::easyGuess() {

}


Coord AI::mediumGuess() {
	int row, col;
	bool validGuess = false;
	Coord guess;
	// If the last hit sunk a ship, guess randomly
	if (lastHitSunkShip) {
		row = rand() % 8;
		col = rand() % 8;
		offset = offsetSign = 1;
	}
	// If the last hit did not sink a ship, guess nearby 
	// until a ship sinks
	else {
		row = firstHitOnShip.row; //Row of the first guess that hit current ship
		col = firstHitOnShip.col; //Col if the last guess that hit current ship

		//Loop until next generated row and col are within bounds (0 - 7)
		while (!validGuess) {
			// If guessed right of first hit and missed, guess left next time
			if (!horizChecked && (offsetSign == 1) && !lastGuessWasHit) {
				offsetSign = -1;
				offset = 1;
			}
			// If guessed left of first hit and missed, guess down next time
			else if (!horizChecked && (offsetSign == -1) && !lastGuessWasHit) {
				offsetSign = 1;
				offset = 1;
				horizChecked = true;
			}
			// If guessed below first hit and missed, guess above next time
			else if (horizChecked && (offsetSign == 1) && !lastGuessWasHit) {
				offsetSign = -1;
				offset = 1;
			}
			//Note: No else branch because it is impossible to exhaust every direction
			//without sinking a ship

			// If the AI has not tried guessing horizontal in both directions,
			// continue guessing horizontally
			if (!horizChecked) {
				//Check that row and col for next guess would be in bounds
				if (myBoard->isValid(col + offset, row)) {
					validGuess = true;
					col += offset;
					offset += offsetSign;
				}
				//If next guess would be outside of bounds, guess left instead of right
				else {
					offset = 1;
					offsetSign = -1;
				}
			}
			// If the AI has guessed both directions horizontally and missed,
			// try guessing vertically
			else {
				//Check that row and col for next guess would be in bounds
				if (myBoard->isValid(col, row + offset)) {
					validGuess = true;
					row += offset;
					offset += offsetSign;
				}
				//If next guess would be out of bounds, guess up instead of down
				else {
					offset = 1;
					offsetSign = -1;
				}
			} 
		}
		guess = { row, col };
		return guess;
	}
}

Coord AI::hardGuess(Players* otherPlayer) {

}

void AI::takeTurn(Players* otherPlayer) {
	Coord guess;
	switch (difficulty) {
	case 1:
		guess = this->easyGuess();
		break;
	case 2:
		guess = this->mediumGuess();
		break;
	case 3:
		guess = this->hardGuess(otherPlayer);
		break;
	}

	/* ---------------------------------------------------
	TODO: Use guess to update both player's boards.
	------------------------------------------------------
	TODO: If the difficulty is medium, set the following
	variables:

		firstHitOnShip  - If the lastGuessWasHit is false
			and the current guess is a hit, update to the
			value of the current guess.
		lastGuessWasHit - true if last guess hit a ship
			and false otherwise
		lastHitSunkShip - true if last guess sunk a ship 
			and false otherwise

	Ignore both offset and offsetSign; they're updated 
	as needed in the mediumGuess method and are used
	to determine where the next guess is in relation
	to firstHitOnShip.
	-----------------------------------------------------*/
}
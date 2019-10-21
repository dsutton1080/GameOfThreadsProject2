#include "AI.h"
#include <stdlib.h>
#include <time.h>

AI::AI(int difficulty, Players* otherPlayerPtr) {
	srand(time(NULL));
	this->ID = "AI";
	this->difficulty = difficulty;
	this->otherPlayer = otherPlayerPtr;

	//Initialize variables needed for medium difficulty
	//-------------------------------------------------
	this->lastHitSunkShip = true; //Initiallzed to true to on medium
								  //the AI will start by guessing randomly
	this->lastGuessWasHit = false;
    this->horizChecked = false;
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
    bool coordPlaced = false;


    ShipTracker shipTracker;
    CoordHitTracker coordTracker(Coord {-1,-1});

	for (int size = numShips; size > 0; size--) {
        shipTracker = ShipTracker();
		row = rand() % 8;
		col = rand() % 8;
		dir = directions[rand() % 4];

		while (count < size) {
			markedCols[count] = col;
			markedRows[count] = row;
			if (count == 0) {
				if (myBoard.isValid(col, row)) {
					myBoard.markShips(col, row);
                    coordPlaced = true;
				}
				else {
                    coordPlaced = false;
					row = (rand() % 8);
					col = (rand() % 8);
				}
			}
			else {
				if (dir == 'u' && myBoard.isValid(col, row - 1)) {
					myBoard.markShips(col, row - 1);
					row--;
                    coordPlaced = true;
				}
				else if (dir == 'd' && myBoard.isValid(col, row + 1)) {
					myBoard.markShips(col, row + 1);
					row++;
                    coordPlaced = true;
				}
				else if (dir == 'l' && myBoard.isValid(col - 1, row)) {
					myBoard.markShips(col - 1, row);
					col--;
                    coordPlaced = true;
				}
				else if (dir == 'r' && myBoard.isValid(col + 1, row)) {
					myBoard.markShips(col + 1, row);
					col++;
                    coordPlaced = true;
				}
				else {
                    coordPlaced = false;
					for (int i = 0; i <= count; i++) {
						myBoard.unmarkShips(markedCols[i], markedRows[i]);
					}
					count = 0;
					row = rand() % 8;
					col = rand() % 8;
					dir = directions[rand() % 4];
				}
			}
            if (coordPlaced) {
                coordTracker = CoordHitTracker(Coord{ row, col });
                shipTracker.appendCoordTracker(coordTracker);
                count++;
            }
		}
		this->fleetTracker.appendShipTracker(shipTracker);
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
	int row, col;
	do {
		row = rand() % 8;
		col = rand() % 8;
	} while(this->hasGuessedCoord(Coord {row, col}));
	
	return Coord {row, col};
}


Coord AI::mediumGuess() {
	int guessRow, guessCol;
	bool validGuess = false;
	// If the last hit sunk a ship, guess randomly
	if (lastHitSunkShip) {
		guessRow = rand() % 8;
		guessCol = rand() % 8;
        offset = 1;
        offsetSign = 1;
        horizChecked = false;
        return Coord{ guessRow, guessCol };
	}
	// If the last hit did not sink a ship, guess nearby 
	// until a ship sinks
	else {
		guessRow = firstHitOnShip.row; //Row of the first guess that hit current ship
		guessCol = firstHitOnShip.col; //Col of the last guess that hit current ship

		//Loop until next generated row and col are within bounds (0 - 7)
		while (!validGuess) {
            if (!lastGuessWasHit) {
                // If guessed right of first hit and missed, guess left next time
                if (!horizChecked && (offsetSign == 1)) {
                    offsetSign = -1;
                    offset = -1;
                }
                // If guessed left of first hit and missed, guess down next time
                else if (!horizChecked && (offsetSign == -1)) {
                    offsetSign = 1;
                    offset = 1;
                    horizChecked = true;
                }
                // If guessed below first hit and missed, guess above next time
                else if (horizChecked && (offsetSign == 1)) {
                    offsetSign = -1;
                    offset = -1;
                }
                //Note: No else branch because it is impossible to exhaust every direction
                //without sinking a ship
            }
			// If the AI has not tried guessing horizontal in both directions,
			// continue guessing horizontally
			if (!horizChecked) {
				//Check that row and col for next guess would be in bounds
				if (guessCol + offset <= 7 && guessCol + offset >= 0) {
					validGuess = true;
					guessCol += offset;
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
				if (guessRow + offset <=7 && guessRow + offset >= 0) {
					validGuess = true;
					guessRow += offset;
					offset += offsetSign;
				}
				//If next guess would be out of bounds, guess up instead of down
				else {
					offset = 1;
					offsetSign = -1;
				}
			} 
		}
        return Coord{ guessRow, guessCol };
	}
}

Coord AI::hardGuess() {
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if(this->otherPlayer->getLocationChar(i, j) == 'S') return Coord {i, j};
		}
	}
}

Coord AI::takeTurn() {
	Coord guess;

	switch (difficulty) {
	case 1:
		guess = this->easyGuess();
		break;
	case 2:  
		guess = this->mediumGuess();
		break;
	case 3:
		guess = this->hardGuess();
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
	return guess;
}

Coord AI::takeSpecialShot() {return takeTurn();}

void AI::guessFeedbackSignal() {
	if(!lastGuessWasHit && otherPlayer->wasHitPrev()) this->firstHitOnShip = otherPlayer->getLastHitCoord();
	this->lastGuessWasHit = otherPlayer->wasHitPrev();
	this->lastHitSunkShip = (otherPlayer->wasSunkPrevHit());
}
#include "AI.h"
#include <stdlib.h>
#include <time.h>

AI::AI(int difficulty) : Players() {
	srand(time(NULL));
	this->difficulty = difficulty;
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
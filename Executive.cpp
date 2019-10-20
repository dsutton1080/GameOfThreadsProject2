#include <iostream>
#include <fstream>
#include <string>
#include "Executive.h"

//Constructor of the Executive class
Executive::Executive(){
  displayLogo();
}
//Destructor of the Executive class
Executive::~Executive(){
}
//Displays the logo created for the Battleship game
void Executive::displayLogo(){
  std::cout << " ____        _   _   _      ____  _     _\n"
    << "| __ )  __ _| |_| |_| | ___/ ___|| |__ (_)_ __\n"
    << "|  _ \\ / _` | __| __| |/ _ \\___ \\| '_ \\| | '_ \\\n"
    << "| |_) | (_| | |_| |_| |  __/___) | | | | | |_) |\n"
    << "|____/ \\__,_|\\__|\\__|_|\\___|____/|_| |_|_| .__/\n"
    << "                                        |_|\n";
}
//Displays the menu that is seen when the game begins
//The menu continues to ask for input until either a new game is started
//of exit is choosen
int Executive::displayMenu(){
    std::cout << "\nPlease make a selection: \n";
    std::cout << "1. Start a new single player game\n";
    std::cout << "2. Start a new two player game\n";
    std::cout << "3. Exit\n";
    int choice = 0;
	while (choice != 3) {
		std::cout << "\nEnter your choice: ";
		std::cin >> choice;
		while (std::cin.fail() || choice > 2 || choice < 1){
        std::cin.clear();
        std::cin.ignore(INT8_MAX, '\n');
        std::cout << "Invalid selection, try again.\n";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        }
        if(choice == 1) {
            return(1 + (10 * displayMenuDifficultyAI()));
        }
        else if(choice == 2) {
            return(2 + (10 * displayMenuGameMode(false)));
        }
        else if(choice == 3) {
            std::cout << "Goodbye!\n";
            exit(0);
        }
    }
}

int Executive::displayMenuDifficultyAI() {
  std::cout << "\nPlease make a selection: \n";
  std::cout << "1. Easy difficulty AI\n";
  std::cout << "2. Medium difficulty AI\n";
  std::cout << "3. Hard difficulty AI\n";
  std::cout << "4. Exit\n";
  int choice = 0;
  while (choice != 4) {
		std::cout << "\nEnter your choice: ";
		std::cin >> choice;
		while (std::cin.fail() || choice > 4 || choice < 1){
        std::cin.clear();
        std::cin.ignore(INT8_MAX, '\n');
        std::cout << "Invalid selection, try again.\n";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        }
        if(choice == 1) {
            return(1 + (10 * displayMenuGameMode(false)));
        }
        else if(choice == 2) {
            return(2 + (10 * displayMenuGameMode(false)));
        }
        else if(choice == 3) {
            return(3 + (10 * displayMenuGameMode(true)));
        }
        else if(choice == 4) {
            std::cout << "Goodbye!\n";
            exit(0);
        }
    }
}

int Executive::displayMenuGameMode(bool isAIHardMode) {
  std::cout << "\nPlease make a selection: \n";
  std::cout << "1. Normal Battleship\n";
  std::cout << "2. Normal Battleship with a once-per-round 'Special Shot'\n";
  std::cout << "3. Special Game Type: Make-It Take-It\n";
  std::cout << "4. Exit\n";
  int choice = 0;
  while (choice != 4) {
		std::cout << "\nEnter your choice: ";
		std::cin >> choice;
		while (std::cin.fail() || choice > 4 || choice < 1){
        std::cin.clear();
        std::cin.ignore(INT8_MAX, '\n');
        std::cout << "Invalid selection, try again.\n";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        }
        if(choice == 1) {
            return(1);
        }
        else if(choice == 2) {
            return(2);
        }
        else if(choice == 3) {
            if(isAIHardMode) {
              std::cout << "BEWARE: Playing this Special Game Mode on hard mode will "
              << "result in an immediate loss if you are to miss even a single shot. We wish you good luck.";
            }
            return(3);
        }
        else if(choice == 4) {
            std::cout << "Goodbye!\n";
            exit(0);
        }
    }
}

void Executive::spawnGame(int gameEncoding) {
  switch(gameEncoding) {
    //** Two Player Games **//

    // Normal game
    case 12: runGame(1,0); break;

    // Normal game w/ special shot mode
    case 22: runGame(2,0); break;

    // Make-it Take-it game mode
    case 32: runGame(3,0); break;


    //** One-player Games **//

    // easy AI, normal game mode
    case 111: runGame(1,1); break;

    // medium AI, normal game mode
    case 121: runGame(1,2); break;

    // hard AI, normal game mode
    case 131: runGame(1,3); break;

    // easy AI, special shot enabled
    case 211: runGame(2,1); break;

    // medium AI, special shot enabled
    case 221: runGame(2,2); break;

    // hard AI, special shot enabled
    case 231: runGame(2,3); break;

    // easy AI, Make-it Take-it mode
    case 311: runGame(3,1); break;

    // medium AI, Make-it Take-it mode
    case 321: runGame(3,2); break;

    // hard AI, Make-it Take-it mode
    case 331: runGame(3,3); break;

  }
}

//Handles processing the majority of the functionality within the game
//Sets players name, calls the setShip method to begin setting the ships,
//and handles swapping turns for each player until the game is won
void Executive::run(){
int gameEncoding;
 while(true) {
   gameEncoding = displayMenu();
   spawnGame(gameEncoding);
 }
}

void Executive::runGame(int gamemode, int aiDifficulty) {
  Players* p1;
  Players* p2;
  p1 = new Players();
  if(aiDifficulty == 0) {
    p2 = new Players();
  } else {
    p2 = new AI(aiDifficulty, p1);
  }

  int numShips = getNumberOfShips();

  p1->setIDinteractive();
  p2->setIDinteractive(); // If AI, this does nothing

  p1->setShips(numShips);
  p2->setShips(numShips);

  switch (gamemode) {
    // Normal Game Mode
    case 1: runNormal(p1, p2); break;
    // Special Shot Game Mode
    case 2: runSpecialShot(p1, p2); break;
    // Make-it Take-it Game Mode
    case 3: runMakeItTakeIt(p1, p2); break;
  }

  delete p1;
  delete p2;

}

void Executive::runNormal(Players* p1, Players* p2) {
  while(true){
        if(playerTurnProcedure(p1, p2)) break;
        if(playerTurnProcedure(p2, p1)) break;
    }
}

void Executive::runSpecialShot(Players* p1, Players* p2) {
  Players* playersArr[2] = {p1, p2};
  bool hasShots[2] = {true, true};
  int i = 0;
  while(true){
    if(hasShots[i]){
      if(promptSpecialShot(playersArr[i])){
        hasShots[i] = false;
        if(specialShotProcedure(playersArr[i],playersArr[(i+1) % 2])) break;
      } else {
        if(playerTurnProcedure(playersArr[i],playersArr[(i+1) % 2])) break;
      }
    } else {
      if(playerTurnProcedure(playersArr[i],playersArr[(i+1) % 2])) break;
    }
    i = (i + 1) % 2;
  }
}

void Executive::runMakeItTakeIt(Players* p1, Players* p2) {
  Players* players[2] = {p1, p2};
  int i = 0;
  bool stay = false;

  while(true){
        stay = false;
        if (playerTurnProcedure(players[i], players[1 - i])) {
            break;
        }
        else if (players[1 - i]->wasHitPrev()) {
            stay = true;
            std::cout << "It is still " << players[i]->getID() << "'s turn to guess.\n";
        }
        if(!stay) i = 1 - i;
    }
}

//Prompts the user to enter how many ships to be used during the game
//between 1 and 5 ships allowed. Prompts user until valid input is
//establised
int Executive::getNumberOfShips(){
  int numberOfShips = 0;
  std::cout << "\n\nGreat! Now lets decide how many ships to play with.\n";
  std::cout << "The number of ships must be at least 1 and no more than 5.\n";
  std::cout << "Enter the number of ships(1-5): ";
  std::cin >> numberOfShips;
  std::cin.clear();
  while (std::cin.fail() || numberOfShips > 5 || numberOfShips < 1){
    std::cin.clear();
    std::cin.ignore(INT8_MAX, '\n');
    std::cout << "Invalid number of ships, try again.\n";
    std::cout << "\nEnter the number of ships: ";
    std::cin >> numberOfShips;
  }
  return numberOfShips;
}

//Clear Screen by Printing Empty line to avoid players can see each others' boards
void Executive::clearScreen(){
  for(int i = 0 ; i < 10 ; i++){
    std::cout<<"\n\n\n\n\n\n\n\n\n\n";
  }
}

//Prompts user to continue when they set their ship ready
void Executive::pressToContinue(){
  char press;
  std::cout<<"Type 'R' to continue.\n";
  std::cin>>press;
  press = (toupper(press));
  while(press != 'R'){
    std::cout<<"Invalid input. Press 'R' to continue.\n";
    std::cin>>press;
    press= (toupper(press));
  }
}

void Executive::guessFeedbackMsg(bool status, int row, char col){
  if(status) {
    std::cout << "HIT (" << col << ", " << row << ")!\n";
  }else{
    std::cout << "MISSED (" << col << ", " << row << ")!\n";
  }
}

void Executive::sunkFeedbackMsg(int shipSize) {
  std::cout << "You SUNK the other player's " << toShipName(shipSize) << "!\n";
}

bool Executive::playerTurnProcedure(Players* current, Players* other) {
  if (!(current->isAI())) {
      current->getBoards();
      std::cout << "\n" << current->getID() << " it's your turn to fire!\n";
  }
  else {
      std::cout << "\nAI Turn.\n";
  }
  Coord guess = current->takeTurn();
  char column = charConvertInverse(guess.col);
  int row = guess.row;
  bool hitStatus = false;
  other->trackShot(Coord {row, charConvert(column)});
  current->guessFeedbackSignal();
  if(other->getHit(column, row) == true){
      hitStatus = true;
      other->markMyHits(column, row);
      current->markTheirHits(column, row);

      if(other->hasLost() == true){
        current->markMyHits(column, row);
        std::cout << current->getID() << " has won the game!!!\n";
        if(current->isAI()) std::cout << other->getID() << ", you'll get'em next time!\n";
        current->getOffensiveBoard();
        current->getDefensiveBoard();
        return(true);
      }
  }
  else{
      other->markMyMisses(column, row);
      current->markTheirMisses(column, row);
  }
  //clearScreen();
  guessFeedbackMsg(hitStatus, row, charConvertInverse(column));
  int sunkLength = other->prevSunkLength();
  if(sunkLength > 0) sunkFeedbackMsg(sunkLength);
  pressToContinue();
  return(false);
}

bool Executive::promptSpecialShot(Players* p) {
  if(p->isAI()) {
    return(rand() % 2 == 1 ? true : false);
  } else {
    char input = ' ';
    while(true) {
      std::cout << "Use your special shot? (y/n): ";
      std::cin >> input;
      if(input == 'Y' || input == 'y') return true;
      else if(input == 'N' || input == 'n') return false;
      std::cout << "\nInvalid input. Please enter 'y' or 'n'.\n";
    }
  }
}

int Executive::promptSpecialShotSelection(Players* p) {
  if(p->isAI()) {
    return((rand() % 4) + 1);
  } else {
    int input = 0;
    std::cout << "\nPlease make a selection for your type of special shot: \n";
    std::cout << "1.\n"; printSpecialShotOption(1);
    std::cout << "\n\n2.\n"; printSpecialShotOption(2);
    std::cout << "\n\n3.\n"; printSpecialShotOption(3);
    std::cout << "\n\n4.\n"; printSpecialShotOption(4);
    while(true) {
      std::cin >> input;
      if(input > 0 && input < 5) return input;
      else std::cout << "\nInvalid input. Valid entries are 1-4. Input: ";
    }
  }
}

void Executive::printSpecialShotOption(int option) {
  Coord* coords = specialShotToCoords(option, Coord {2,2});
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      if(isInCoords(coords, i, j)) std::cout << "+";
      else std::cout << "~";
    }
    std::cout << "\n";
  }
  delete[] coords;
}

bool Executive::specialShotProcedure(Players* current, Players* other) {
  current->getBoards();
  int shotEncoding = promptSpecialShotSelection(current);

  Coord guess = current->takeSpecialShot();
  int row = guess.row;
  int column = guess.col;

  Coord center = Coord { row, column };
  Coord* shotCoords = specialShotToCoords(shotEncoding, center);

  bool hitCoord;
  for(int i=0; i < 9; i++) {
    if(isCoordInBounds(shotCoords[i], 0, 7, 0, 7)) {
      other->trackShot(Coord {row, column});
      current->guessFeedbackSignal();
      if(other->getHit(charConvertInverse(shotCoords[i].col), shotCoords[i].row))
      {
        other->markMyHits(column, row);
        current->markTheirHits(column, row);
        guessFeedbackMsg(true, shotCoords[i].row, charConvertInverse(shotCoords[i].col));
        int sunkLength = other->wasSunkPrev();
        if(sunkLength > 0) sunkFeedbackMsg(sunkLength);
      }
      else {
        other->markMyMisses(column, row);
        current->markTheirMisses(column, row);
        guessFeedbackMsg(false, shotCoords[i].row, charConvertInverse(shotCoords[i].col));
      }
    }
  }
  if(other->hasLost() == true){
    current->markMyHits(column, row);
    std::cout << current->getID() << " has won the game!!!\n";
    if(current->isAI()) std::cout << other->getID() << ", you'll get'em next time!\n";
    current->getOffensiveBoard();
    current->getDefensiveBoard();
    return(true);
  }
  return false;
}

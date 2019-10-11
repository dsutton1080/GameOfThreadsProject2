#include <iostream>
#include <fstream>
#include <string>
#include "Executive.h"

//Constructor of the Executive class
Executive::Executive(){
  displayLogo();
  row = numberOfShips = choice = 0;
  column = ' ';
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
              std::cout << "BEWARE: Playing this Special Game Mode on hard mode will \
              result in an immediate loss if you are to miss even a single shot. We wish you good luck.";
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


void Executive::runTwoPlayerGame(int gamemode) {
  std::cout << "Two Player Game!\n";
}

void Executive::runOnePlayerGame(int gamemode, int aiLevel) {
  std::cout << "One Player Game!\n";
}

//Handles processing the majority of the functionality within the game
//Sets players name, calls the setShip method to begin setting the ships,
//and handles swapping turns for each player until the game is won
void Executive::run(){
//  Players player1tmp;
//  Players player2tmp;
//  player1 = &player1tmp;
//  player2 = &player2tmp;
int gameEncoding;
 while(true) {
   gameEncoding = displayMenu();
   spawnGame(gameEncoding);
 }
//  setPlayer1Name();
//  setPlayer2Name();

//  getNumberOfShips();

//  player1->setShips(numberOfShips);
//  clearScreen();
//  player2->setShips(numberOfShips);
//  clearScreen();
//  //Swaps between players 1 and 2, giving each a chance to "shoot"
//  //at the opponents board. Informs the user if their shot was a hit
//  //or a miss
//  std::cout << "The ships are set and its time for the game to begin!\n";
//  std::cout << "Let's play some BATTLESHIP!!\n";

//   while(true){
//       if(playerTurnProcedure(player1, player2)) break;
//       if(playerTurnProcedure(player2, player1)) break;
//   }
//   run();
}

void Executive::runGame(int aiDifficulty, int gamemode) {
  Players* p1, p2;
  p1 = new Players();
  if(aiDifficulty == 0) {
    p2 = new Players();
  } else {
    p2 = new AI(aiDifficulty);
  }

  

  p1->setIDinteractive();
  p2->setIDinteractive(); // If AI, this does nothing

  p1->setShips();

}

//Prompts the user to enter how many ships to be used during the game
//between 1 and 5 ships allowed. Prompts user until valid input is
//establised
void Executive::getNumberOfShips(){
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
}
//Prompts the user to enter what column is to be targeted
//Prompts user until valid input is established
void Executive::getColumn(){
  std::cout << "\nEnter the column letter: ";
  std::cin >> column;
  column = (toupper(column));
  while(column < 65 || column > 72){
    if(column < 65 || column > 72){
    std::cout << "Invalid selection, try again\n";
    std::cout << "Enter the column letter: ";
    std::cin >> column;
   }
   else{
     std::cin >> column;
   }
  }
}
//Prompts the user to enter what row is to be targeted
//Prompts user until valid input is established
void Executive::getRow(){
  std::cout << "\nEnter the row number: ";
  std::cin >> row;
  while (std::cin.fail() || row > 7 || row < 0){
    std::cin.clear();
    std::cin.ignore(INT8_MAX, '\n');
    std::cout << "Invalid selection, try again.\n";
    std::cout << "\nEnter the row number: ";
    std::cin >> row;
  }
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
  std::cout<<"Change users, then type 'R' to continue.\n";
  std::cin>>press;
  press = (toupper(press));
  while(press != 'R'){
    std::cout<<"Invalid input. Press 'R' to continue.\n";
    std::cin>>press;
    press= (toupper(press));
  }
}

void Executive::guessFeedbackMsg(bool status){
  if(status) {
    std::cout << "HIT!\n";
  }else{
    std::cout << "MISS!\n";
  }
}

bool Executive::playerTurnProcedure(Players* current, Players* other) {
  current->getBoards();
  std::cout << "\n" << current->getID() << " it's your turn!\n";
  getColumn();
  getRow();
  bool hitStatus = false;
  if(other->getHit(column, row) == true){
      hitStatus = true;
      other->markMyHits(column, row);
      current->markTheirHits(column, row);

      if(other->hasLost() == true){
        current->markMyHits(column, row);
        std::cout << current->getID() << " has won the game!!!\n";
        current->getOffensiveBoard();
        current->getDefensiveBoard();
        return(true);
      }
  }
  else{
      other->markMyMisses(column, row);
      current->markTheirMisses(column, row);
  }
  clearScreen();
  guessFeedbackMsg(hitStatus);
  pressToContinue();
  return(false);
}

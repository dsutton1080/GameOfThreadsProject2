#include "Players.h"
#include <vector>

Players::Players(){
  ID = " ";
	allSet = false;
}

Players::~Players(){
}

void Players::setID(std::string name){
    this->ID = name;
}
std::string Players::getID(){
    return this->ID;
}
void Players::setShips(int number){
  int row;
  char column;
  char orientation = ' ';
  int tempRow;
  char tempColumn;

  std::cout << "\n" << this->ID << " it's your turn to start setting your ships!\n\n";
  std::cout << "The ships can only be placed vertically or horizontally\n";
  std::cout << "Placing a ship diagonally is not allowed.\n";

  ShipTracker shipTracker;
  CoordHitTracker coordTracker(Coord {-1,-1});

  for(int i = 0; i < number; i++){
  shipTracker = ShipTracker();

    if(i == 0){
      std::cout << "\n\nThis ship is a 1 X " << i+1 << " ship.\n";
      myBoard.displayDefensiveBoard();
      column = getColumn();
      row = getRow();
      myBoard.markShips(charConvert(column), row);
	    coordTracker = CoordHitTracker(Coord{ row, charConvert(column) });
	    shipTracker.appendCoordTracker(coordTracker);
      this->fleetTracker.appendShipTracker(shipTracker);
    }
    else{
      myBoard.displayDefensiveBoard();
      std::cout << "\nThis ship is a 1 X " << i+1 << " ship.\n";
      std::cout << "Enter 'V' to place the ship vertically, and 'H' to place the ship horizontally: ";
      std::cin >> orientation;
      orientation = toupper(orientation);
      while(orientation != 'V' && orientation != 'H'){
          std::cout << "Invalid input.\n";
          std::cout << "Enter 'V' for vertically or 'H' for horizontally: ";
          std::cin >> orientation;
          orientation = toupper(orientation);
          std::cout << orientation << "\n";
      }
      for(int j = 0; j < i+1; j++){
          if(j == 0){
            std::cout << "This is the first section to be placed.\n";
          }
          else if(j == 1){
            std::cout << "This is the second section to be placed.\n";
          }
          else if(j == 2){
            std::cout << "This is the third section to be placed.\n";
          }
          else if(j == 3){
            std::cout << "This is the fourth section to be placed.\n";
          }
          else if(j == 4){
            std::cout << "This is the fifth section to be placed.\n";
          }
          myBoard.displayDefensiveBoard();
          std::cout << "\n" << this->ID << " it's your turn!\n\n";
          if(orientation == 'V'){
              do {
                  column = getColumn();
                  if (j > 0) {
                      while (column != tempColumn) {
                          std::cout << "Column must be the same as the previous placement.\n";
                          column = getColumn();
                      }
                  }
                  row = getRow();
                  if (j > 0) {
                      while ((row != tempRow + 1) && (row != tempRow - 1)) {
                          std::cout << "Row must be adjacent to the previous placement.\n";
                          row = getRow();
                      }
                  }
                  if (this->getLocationChar(row, charConvert(column)) != '~') {
                      std::cout << "That space is already occupied!\n";
                  }
              } while (this->getLocationChar(row, charConvert(column)) != '~');
          }
          else if(orientation == 'H'){      
              do {
                  column = getColumn();
                  if (j > 0) {
                      std::cout << charConvert(column) << " " << charConvert(tempColumn) << '\n';
                      while ((charConvert(column) != charConvert(tempColumn)+1) && 
                                    (charConvert(column) != charConvert(tempColumn)-1) )  {
                          std::cout << "Column must be adjacent to the previous placement.\n";
                          column = getColumn();
                      }
                  }
                  row = getRow();
                  if (j > 0) {
                      while (row != tempRow) {
                          std::cout << "Row must be the same as the previous placement.\n";
                          row = getRow();
                      }
                  }
                  if (this->getLocationChar(row, charConvert(column)) != '~') {
                      std::cout << "That space is already occupied!\n";
                  }
              } while (this->getLocationChar(row, charConvert(column)) != '~');
          }
        myBoard.markShips(charConvert(column), row);
		    coordTracker = CoordHitTracker(Coord{ row, charConvert(column) });
	      shipTracker.appendCoordTracker(coordTracker);
        tempRow = row;
        tempColumn = (toupper(column));
      }
	    this->fleetTracker.appendShipTracker(shipTracker);
    }
  }
  //set the column and row on the defensive map
  allSet = true;
}
void Players::getBoards() const {
	myBoard.displayBoth();
}
void Players::getOffensiveBoard() const {
	myBoard.displayOffensiveBoard();
}
void Players::getDefensiveBoard() const {
	myBoard.displayDefensiveBoard();
}
char Players::getColumn(){
    char column = ' ';
    std::cout << "Enter the column letter: ";
    std::cin >> column;
    column = (toupper(column));
    while(column < 65 || column > 72){
        if(column < 65 || column > 72){
            std::cout << "Invalid selection, try again\n";
            std::cout << "Enter a valid column letter: ";
            std::cin >> column;
            column = (toupper(column));
        }
    }
    return column;
}
int Players::getRow(){
    int row = 0;
    std::cout << "Enter the row number: ";
    std::cin >> row;
    while (std::cin.fail() || row > 7 || row < 0){
        std::cin.clear();
        std::cin.ignore(INT8_MAX, '\n');
        std::cout << "Invalid selection, try again.\n";
        std::cout << "Enter a valid row number: ";
        std::cin >> row;
    }
    return row;
}
void Players::markMyHits(char column, int row){
    myBoard.ownBoardHit(charConvert(column), row);
}
void Players::markMyMisses(char column, int row){
    myBoard.ownBoardMiss(charConvert(column), row);
}
void Players::markTheirHits(char column, int row){
    myBoard.otherBoardHit(charConvert(column), row);
}
void Players::markTheirMisses(char column, int row){
    myBoard.otherBoardMiss(charConvert(column), row);
}
bool Players::shipsSet(){
    return this->allSet;
}
bool Players::hasLost(){
    if(myBoard.gameWon() == true){
        return true;
    }
    else{
        return false;
    }
}
bool Players::getHit(char column, int row){
    if(myBoard.getLocation(charConvert(column), row) == 'S' || 
                myBoard.getLocation(charConvert(column), row) == 'H') {
        return true;
    }
    else{
        return false;
    }
}

void Players::cleanBoard(){
  myBoard.clearBoards();
}

void Players::setIDinteractive() {
    if (!(this->isAI())) {
        std::string name = " ";
            std::cout << "Enter the name of this player: ";
            std::cin >> name;
            std::cout << "Welcome " << name << "!\n";
            this->setID(name);
    }
}

bool Players::isAI() {
  return false;
}

bool Players::wasHitPrev() {
  return fleetTracker.hitOnLastGuess();
}

bool Players::wasSunkPrev() {
  return(prevSunkLength() > 0);
}

bool Players::wasSunkPrevHit() {
    return fleetTracker.sunkOnLastHit();
}

int Players::prevSunkLength() {
  return fleetTracker.sunkLengthOnLastGuess();
}

void Players::trackShot(Coord c) {
  this->fleetTracker.attemptHit(c);
}

Coord Players::getLastHitCoord() {
  return this->fleetTracker.getLastCoordHit();
}

Coord Players::takeTurn() {
  int coltmp = charConvert(getColumn());
  int rowtmp = getRow();
  return Coord {rowtmp, coltmp};
}

Coord Players::takeSpecialShot() {
  int coltmp = charConvert(getColumnInput("Enter the column for the center of your special shot (A-H): ", 0, 7));
  int rowtmp = getRowInput("Enter the row for the center of your special shot (0-7): ", 0, 7);
  return Coord {rowtmp, coltmp};
}

void Players::guessFeedbackSignal() {}

bool Players::hasGuessedCoord(Coord c) {
  int spot = this->myBoard.getLocation(c.col, c.row);
  return(spot == 'H' || spot == 'M');
}

char Players::getLocationChar(int row, int col) {
  return this->myBoard.getLocation(col, row);
}

std::vector<std::tuple<int, int>> Players::returnShipList(){
  return this->myBoard.returnPossibleCoords();
}
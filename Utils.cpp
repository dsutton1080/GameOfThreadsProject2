
#include "Utils.h"


bool Coord::operator==(Coord c) const {
    if (c.row == row && c.col == col) {
        return true;
    }
    else {
        return false;
    }
}

// Returns whether a coordinate object falls within the specified bounds (inclusive)
bool isCoordInBounds(Coord c, int rowLow, int rowHigh, int colLow, int colHigh) {
    return(
        c.row >= rowLow && c.row <= rowHigh && c.col >= colLow && c.col >= colHigh
    );
}

// Checks to see whether a coord is on 0-7 x 0-7 board
bool isValidCoord(Coord c) {
    return isCoordInBounds(c, 0, 7, 0, 7);
}

// Checks to see if an array of coords is all on the playing surface
bool isValidCoords(Coord coordArr[]) {
    // 9 is array size because each special shot will have 9 "attack points"
    for(int i = 0; i < 9; i++) {
        if(!isValidCoord(coordArr[i])) return false;
    }
    return true;
}

// Checks to see whether the center coordinate chosen for the special shot is locationally-valid so that 
// the entire shot fits on the board
bool isValidCenterCoord(Coord c, int specialShotType) {
    return specialShotType == 1 ? isCoordInBounds(c, 1, 6, 1, 6) : isCoordInBounds(c, 2, 5, 2, 5); 
}

std::vector<Coord> coordsFromRowColOffsets(Coord c, Coord* offsets) {
    std::vector<Coord> vect;
    for(int i = 0; i < 9; i++) {
        vect.push_back(Coord {c.row + offsets[i].row, c.col + offsets[i].col});
    }
    return vect;
}

// Returns a list of Coord objects given the shot type and a center Coord
std::vector<Coord> specialShotToCoords(int shotType, Coord center) {
    switch (shotType)
        {
        case 1: {
            Coord arr[9] = {{1,-1}, {1,0}, {1,1}, {0,-1}, {0,0}, {0,1}, {-1,-1}, {-1,0}, {-1,1}};
            return coordsFromRowColOffsets(center, arr);
        }
        case 2: {
            Coord arr[9] = {{2,-2}, {2,0}, {2,2}, {0,-2}, {0,0}, {0,2}, {-2,-2}, {-2,0}, {-2,2}};
            return coordsFromRowColOffsets(center, arr);
        }
        case 3: {
            Coord arr[9] = {{2,-2}, {2,2}, {1,-1}, {1,1}, {0,0}, {-1,-1}, {-1,1}, {-2,-2}, {-2,2}};
            return coordsFromRowColOffsets(center, arr);
        }
        case 4: {
            Coord arr[9] = {{2,0}, {1,0}, {0,-2}, {0,-1}, {0,0}, {0,1}, {0,2}, {-1,0}, {-2,0}};
            return coordsFromRowColOffsets(center, arr);
        }
    }
}

bool isInCoords(const std::vector<Coord>& coords, int row, int col) {
    for(int i = 0; i < 9; i++) {
        if(coords.at(i).row == row && coords.at(i).col == col) return true;
    }
    return false;
}

bool isValidCenterSpecialShotCoord(Coord c, int shotEncoding) {
  if(shotEncoding == 1) {
    return isCoordInBounds(c, 1, 6, 1, 6);
  }
  return isCoordInBounds(c, 2, 5, 2, 5);
}

int getRowInput(std::string msg, int min, int max) {
  int row = 0;
    std::cout << msg;
    std::cin >> row;
    while (std::cin.fail() || row < min || row > max){
      std::cin.clear();
      std::cin.ignore(INT8_MAX, '\n');
      std::cout << "Invalid selection, try again.\n";
      std::cout << "Enter a valid row number: ";
      std::cin >> row;
    }
    return row;
}

char getColumnInput(std::string msg, int min, int max){
    char column = ' ';
    std::cout << msg;
    std::cin >> column;
    column = (toupper(column));

    while(column < (min + 65) || column > (max + 65)){
      std::cout << "Invalid selection, try again\n";
      std::cout << "Enter a valid column letter: ";
      std::cin >> column;
      column = (toupper(column));
    }
    return column;
}

//Converts the letter for column into a number
int charConvert(char temp){
  int columnNumber = 0;
  if(temp == 'A' || temp == 'a'){
    columnNumber = 0;
  }
  else if(temp == 'B' || temp == 'b'){
    columnNumber = 1;
  }
  else if(temp == 'C' || temp == 'c'){
    columnNumber = 2;
  }
  else if(temp == 'D' || temp == 'd'){
    columnNumber = 3;
  }
  else if(temp == 'E' || temp == 'e'){
    columnNumber = 4;
  }
  else if(temp == 'F' || temp == 'f'){
    columnNumber = 5;
  }
  else if(temp == 'G' || temp == 'g'){
    columnNumber = 6;
  }
  else if(temp == 'H' || temp == 'h'){
    columnNumber = 7;
  }
  return columnNumber;
}

char charConvertInverse(int n) {
    switch (n) {
    case 0:
        return 'A';
        break;
    case 1:
        return 'B';
        break;
    case 2:
        return 'C';
        break;
    case 3:
        return 'D';
        break;
    case 4:
        return 'E';
        break;
    case 5:
        return 'F';
        break;
    case 6:
        return 'G';
        break;
    case 7:
        return 'H';
        break;
    }
}

std::string toShipName(int i) {
  switch(i) {
    case 1: return("Submarine");
    case 2: return("Destroyer");
    case 3: return("Cruiser");
    case 4: return("Battleship");
    case 5: return("Carrier");
  }
  return("invalid ship length");
}


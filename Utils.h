#ifndef UTILS
#define UITLS

#include <string>
#include <iostream>
#include <vector>

//A struct representing a coordinate
struct Coord {
    //The row of the coordinate
    int row;
    //The column of the coordinate
    int col;
    /**
    *@brief returns true if the two Coords have the same row and col values
    */
    bool operator==(Coord c) const;
};

bool isCoordInBounds(Coord c, int rowLow, int rowHigh, int colLow, int colHigh);

bool isValidCoord(Coord c);

bool isValidCoords(Coord coordArr[]);

bool isValidCenterCoord(Coord c, int specialShotType);

std::vector<Coord> coordsFromRowColOffsets(Coord c, Coord* offsets);

std::vector<Coord> specialShotToCoords(int shotType, Coord center);

bool isInCoords(const std::vector<Coord>& coords, int row, int col);

bool isValidCenterSpecialShotCoord(Coord c, int shotEncoding);

int getRowInput(std::string msg, int min, int max);

char getColumnInput(std::string msg, int min, int max);

int charConvert(char temp);

char charConvertInverse(int n);

std::string toShipName(int i);


#endif

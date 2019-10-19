#ifndef UTILS
#define UITLS

#include <string>
#include <iostream>
#include <vector>

struct Coord {
    int row;
    int col;
    bool operator==(Coord c) const;
};

bool isCoordInBounds(Coord c, int rowLow, int rowHigh, int colLow, int colHigh);

bool isValidCoord(Coord c);

bool isValidCoords(Coord coordArr[]);

bool isValidCenterCoord(Coord c, int specialShotType);

Coord* coordsFromRowColOffsets(Coord c, Coord* offsets);

Coord* specialShotToCoords(int shotType, Coord center);

bool isInCoords(Coord coords[], int row, int col);

bool isValidCenterSpecialShotCoord(Coord c, int shotEncoding);

int getRowInput(std::string msg, int min, int max);

char getColumnInput(std::string msg, int min, int max);

int charConvert(char temp);

char charConvertInverse(int n);

std::string toShipName(int i);


#endif

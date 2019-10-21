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
/**
*@param
*@pre
*@post
*/
bool isCoordInBounds(Coord c, int rowLow, int rowHigh, int colLow, int colHigh);
/**
*@param
*@pre
*@post
*/
bool isValidCoord(Coord c);
/**
*@param
*@pre
*@post
*/
bool isValidCoords(Coord coordArr[]);
/**
*@param
*@pre
*@post
*/
bool isValidCenterCoord(Coord c, int specialShotType);
/**
*@param
*@pre
*@post
*/
Coord* coordsFromRowColOffsets(Coord c, Coord* offsets);
/**
*@param
*@pre
*@post
*/
Coord* specialShotToCoords(int shotType, Coord center);
/**
*@param
*@pre
*@post
*/
bool isInCoords(Coord coords[], int row, int col);
/**
*@param
*@pre
*@post
*/
bool isValidCenterSpecialShotCoord(Coord c, int shotEncoding);
/**
*@param
*@pre
*@post
*/
int getRowInput(std::string msg, int min, int max);
/**
*@param
*@pre
*@post
*/
char getColumnInput(std::string msg, int min, int max);
/**
*@param
*@pre
*@post
*/
int charConvert(char temp);
/**
*@param
*@pre
*@post
*/
char charConvertInverse(int n);
/**
*@param
*@pre
*@post
*/
std::string toShipName(int i);


#endif

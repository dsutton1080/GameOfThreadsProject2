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
*@param takes a coordinate object, and the bounds for the grid 
*@pre Needs to be passed a non empty Coord object and ints that are not empty 
*@post Returns true if coord is in bounds and false otherwise 
*/
bool isCoordInBounds(Coord c, int rowLow, int rowHigh, int colLow, int colHigh);
/**
*@param takes a coordinate object 
*@pre coordinate object must not be empty 
*@post returns true if the coordinate is in bounds and false otherwise 
*/
bool isValidCoord(Coord c);
/**
*@param takes a coordiante object that is an Array 
*@pre Coord object must not be empty 
*@post returns true if all Coords are in bounds and false otherwise 
*/
bool isValidCoords(Coord coordArr[]);
/**
*@param takes a coordinate object and number representing the specialShotType
*@pre Coord object must not be empty and int must not be null
*@post returns true is coordinate is locationally valid 
*/
bool isValidCenterCoord(Coord c, int specialShotType);
/**
*@param takes a coordinate object 
*@pre helper function 
*@post returns a reference coordinate object 
*/
std::vector<Coord> coordsFromRowColOffsets(Coord c, Coord* offsets);
/**
*@param takes a shotType as an integer and the origin coordinate for shot type
*@pre shotType must not be null and Coord must not be empty 
*@post returns a reference coordinate object 
*/
std::vector<Coord> specialShotToCoords(int shotType, Coord center);
/**
*@param takes a coords list and the coordinates 
*@pre Coords must not be empty and the row and col must not be null 
*@post
*/
bool isInCoords(const std::vector<Coord>&, int row, int col);
/**
*@param takes a coordinate object 
*@pre helper function 
*@post returns true if the coord passed in is a valid special shot coordinate
*/
bool isValidCenterSpecialShotCoord(Coord c, int shotEncoding);
/**
*@param takes a string as a message and the max and min acceptable cin response
*@pre the min and max must not be null 
*@post returns an integer 
*/
int getRowInput(std::string msg, int min, int max);
/**
*@param takes a string as a message and the max and min acceptable cin response
*@pre the min and max must not be null 
*@post returns an integer 
*/
char getColumnInput(std::string msg, int min, int max);
/**
*@param takes a character 
*@pre character must not be empty 
*@post returns a integer that was a conversion of that character 
*/
int charConvert(char temp);
/**
*@param takes an integer 
*@pre integer must not be null
*@post returns a character that was a conversion of that integer
*/
char charConvertInverse(int n);
/**
*@param takes an integer
*@pre integer must not be null
*@post returns a string that is the name of that respective integer value 
*/
std::string toShipName(int i);


#endif

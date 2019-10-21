#ifndef EXECUTIVE_H
#define EXECUTIVE_H
#include "AI.h"

class Executive{
    protected:
      /**
      *@pre none
      *@post Displays the logo for the game
      **/
      void displayLogo();
      /**
      *@pre none
      *@post none
      *@post Prompts the user to enter the number of ships to be
      *     used during gameplay. Between 1 and 5 ships are allowed
      **/
      int getNumberOfShips();
      /**
       *@brief clears the screen.
       */
      void clearScreen();
      /**
       *@brief Continues to next turn after pressing a key.
       */
      void pressToContinue();
      /**
       *@brief Let's the user see if they hit or miss.
       */
      void guessFeedbackMsg(bool status, int row, char col);
      /**
      *@param
      *@pre
      *@post
      */
      void sunkFeedbackMsg(int shipSize);
      /**
       *@brief The sequence procedure performed by each player on their turn.
       * This is to factor out the repetitive code.
       *@return A boolean indicating if the current turn ended the game
      */
      bool playerTurnProcedure(Players* current, Players* other);
      /**
      *@param
      *@pre
      *@return
      */
      bool specialShotProcedure(Players* current, Players* other);
      /**
      *@pre none
      *@return An int indicating the combination of # of players, game type, and AI difficulty
      *@post Displays the top-level menu for the game
      **/
      int displayMenu();

      /**
      *@pre none
      *@return A in indicating the game type and AI difficulty
      */
      int displayMenuDifficultyAI();
      /**
      *@param isHardAIMode: A bool indicating whether the AI is on hard mode
      *@pre none
      *@return An int indicating the game type
      */
      int displayMenuGameMode(bool isHardAIMode);
      /**
      *@param gameEncoding: A number indicating which the chosen settings for # of players, game type, and difficulty
      *@pre gameEncoding was generated from displayMenu() function
      *@post A game with the given set up is run
      */
      void spawnGame(int gameEncoding);
      /**
      *@param gameMode: An int indicating the game mode
      *@param aiLevel: An int indicating the AI difficulty
      *@pre none
      *@post The game is run
      */
      void runGame(int gamemode, int aiLevel);
      /**
      *@param p1: The first player
      *@param p2: The second player (can be AI)
      *@pre none
      *@post A game is run with no special rules
      */
      void runNormal(Players* p1, Players* p2);
      /**
      *@param p1: The first player
      *@param p2: The second player (can be AI)
      *@pre none
      *@post A game is run where players have the option to take one special shot
      */
      void runSpecialShot(Players* p1, Players* p2);
      /**
      *@param p1: The first player
      *@param p2: The second player (can be AI)
      *@pre none
      *@post A game is run where getting a hit allows you to take another turn
      */
      void runMakeItTakeIt(Players* p1, Players* p2);
      /**
      *@param p: A player object
      *@pre p is the current turn player
      *@return Whether the player has indicated that they would like to use their special shot
      */
      bool promptSpecialShot(Players* p);

      Coord promptGuess(Players* current);

      Coord promptSpecialShotCenterCoord(Players* current);

      /**
      *@param p: A player object
      *@pre p is the current turn player
      *@return An int indicating what type of special shot the player chose to use
      */
      int promptSpecialShotSelection(Players* p);
      /**
      *@param option: An int indicating the type of special shot to dsiplay
      *@pre none
      *@post Displays the types of special shots to choose from
      */
      void printSpecialShotOption(int option);
      /**
      *@param gameCode: An int indicating what type of game to run
      *@param p1: A player object
      *@param p2: A player object
      *@pre none
      *@post The appropriate game type is ran
      */
      void runGameHelper(int gamecode, Players* p1, Players* p2);

    public:
        /**
        *@pre none
        *@post primary constructor of the Executive class
        **/
        Executive();
        /**
        *@pre none
        *@post destructor of the Executive class
        **/
        ~Executive();
       /**
        *@pre none
        *@post Handles the majority of functionality within
        *     the game. ets players name, calls the setShip
        *     method to begin setting the ships, and handles
        *     swapping turns for each player until the game is won.
        *     Has many private methods that it uses as helpers.
        **/
        void run();

};
#endif

#ifndef EXECUTIVE_H
#define EXECUTIVE_H
#include "AI.h"

class Executive{
    private:
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

      void sunkFeedbackMsg(int shipSize);
      /**
       *@brief The sequence procedure performed by each player on their turn.
       * This is to factor out the repetitive code.
       *@return A boolean indicating if the current turn ended the game
       */
      bool playerTurnProcedure(Players* current, Players* other);

      bool specialShotProcedure(Players* current, Players* other);

      /**
      *@pre none
      *@return An int indicating the combination of # of players, game type, and AI difficulty
      *@post Displays the top-level menu for the game
      **/
      int displayMenu();

      int displayMenuDifficultyAI();

      int displayMenuGameMode(bool isHardAIMode);

      void spawnGame(int gameEncoding);

      void runGame(int gamemode, int aiLevel);

      void runNormal(Players* p1, Players* p2);

      void runSpecialShot(Players* p1, Players* p2);

      void runMakeItTakeIt(Players* p1, Players* p2);

      bool promptSpecialShot(Players* p);

      Coord promptGuess(Players* current);

      Coord promptSpecialShotCenterCoord(Players* current);

      int promptSpecialShotSelection(Players* p);

      void printSpecialShotOption(int option);

      void runGameHelper(int gamecode, Players* p1, Players* p2);

    public:
        /**
        *@pre none
        *@post primary constructor of the Executive class
        *@post returns nothing
        **/
        Executive();
        /**
        *@pre none
        *@post destructor of the Executive class
        *@post returns nothing
        **/
        ~Executive();
       /**
        *@pre none
        *@post none
        *@post Handles the majority of functionality within
        *     the game. ets players name, calls the setShip
        *     method to begin setting the ships, and handles
        *     swapping turns for each player until the game is won
        **/
        void run();

};
#endif

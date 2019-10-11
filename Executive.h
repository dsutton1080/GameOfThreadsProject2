#ifndef EXECUTIVE_H
#define EXECUTIVE_H
#include "Boards.h"
#include "Players.h"
class Executive{

    private:
        ///Get the row number from user, Get the choice using in interface.
        int row, choice;
        ///Get the col char from user
        char column;
        ///Create an object to access to player class
        Players* player1;
        ///Create another object to access to player class for another player
        Players* player2;
        ///Get the number of ships from user
	    int numberOfShips;

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
        *@post Displays the logo for the game
        **/
        void displayLogo();
       /**
        *@pre none
        *@post none
        *@post Handles the majority of functionality within
        *     the game. ets players name, calls the setShip
        *     method to begin setting the ships, and handles
        *     swapping turns for each player until the game is won
        **/
        void run();
        /**
        *@pre none
        *@post none
        *@post Prompts the user to enter the number of ships to be
        *     used during gameplay. Between 1 and 5 ships are allowed
        **/
        void getNumberOfShips();
        /**
        *@pre none
        *@post none
        *@post Repeatedly prmpts the user for a column letter until
        *     a valid column letter is entered
        **/
        void getColumn();
        /**
        *@pre none
        *@post none
        *@post Repeatedly prmpts the user for a row number until
        *     a valid row number is entered
        **/
        void getRow();
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
        void guessFeedbackMsg(bool status);
        /**
         *@brief The sequence procedure performed by each player on their turn.
         * This is to factor out the repetitive code.
         *@return A boolean indicating if the current turn ended the game
         */
        bool playerTurnProcedure(Players* current, Players* other);

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

};
#endif

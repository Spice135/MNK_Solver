/******************************************************************************/
/*!
\file   main.cpp
\date   09/13/2021
*/
/******************************************************************************/
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>

#include "mnkSolver.h" // mnkSolver class

using namespace std;

// This function runs the m, n, k game
int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        cout << "Incorrect number of parameters given." << endl;
        cout << "Please enter the dimensions of the board separated by a space, followed by the number of pieces needed in a row to win." << endl;
        cout << "Example: mnk.exe 3 3 3" << endl;
        return 0; // Exit program
    }

    // Get cl args, use atoi for no-throw guarantee
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int k = atoi(argv[3]);

    if (m == 0 || n == 0 || k == 0) // Could not convert args to integers
    {
        cout << "Invalid parameters for game" << endl;
        cout << "Please enter the dimensions of the board separated by a space, followed by the number of pieces needed in a row to win." << endl;
        cout << "Example: mnk.exe 3 3 3" << endl;
        return 0; // Exit program
    }

    cout << "Welcome to the m, n, k game. Please remember to enter the row and column of your move separated by a space (1 to m and 1 to n)." << endl;
    cout << "Type in \"undo\" to undo the last move" << endl;
    cout << "Type in \"q\" at any point to end the game." << endl;

    bool gameOver = false; // Is the game over?
    char winner = 0; // Stores the winners name
    mnkSolver game(m, n, k); // Create game with provided arguments
    game.printBoard(); // Print initial board

    cout << "O starts the game" << endl;
    
    while (gameOver == false) // While there are moves left & no one has won
    {
        cout << game.getPlayer() << "'s turn" << endl; // Prompt player for input
        string playerInput;
        getline(cin, playerInput);

        if (playerInput == "q")
            break; // Quit game
        if (playerInput == "undo")
        {
            game.undoMove(); // Undo last move
            game.printBoard(); // Show board after undoing
            continue;
        }

        if (game.addMove(playerInput) == 1)
            cout << "Invalid Move! Please try again" << endl; // Move could not be added
        else
        {
            game.printBoard(); // Print out current board
            winner = game.checkWinner(); // See if someone has won the game (or if board is full)
            if (winner != 0)
                gameOver = true; // Game is over
        }
    }

    if (gameOver)
    {
        if (winner != 'T')
            cout << "Winner is: " << winner << " Congratulations!" << endl; // Show winner
        else
            cout << "The game has ended in a tie." << endl; // Show tie
    }

    cout << "Thanks for playing!" << endl;
    return 0; // Exit program
}

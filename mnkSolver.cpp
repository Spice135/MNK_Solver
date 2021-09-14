/******************************************************************************/
/*!
\file   mnkSolver.cpp
\date   09/13/2021
*/
/******************************************************************************/
#include "mnkSolver.h" // mnkSolver class

// Constructs the mnkSolver class
mnkSolver::mnkSolver(int _m, int _n, int _k) : m(_m), n(_n), k(_k), currMove('O')
{
    movesLeft = m * n; // Number of moves left to play
    for(int i = 0; i < m; ++i)
    {
        vector<char> temp;
        for(int j = 0; j < n; ++j)
            temp.push_back(0); // Create board with all 0s
        board.push_back(temp);
    }
}

// Adds a move to the board, returns 0 if succeeded and 1 if failed
int mnkSolver::addMove(string input)
{
    size_t index = input.find(" "); // Find space
    if (index == string::npos)
        return 1; // No space to separate row and column, invalid input

    int x = atoi(input.substr(0, index).c_str()) - 1;                            // Get row and make it 0 based index
    int y = atoi(input.substr(index + 1, input.size() - 1 - index).c_str()) - 1; // Get column and make it 0 based index
    
    if (x < m && x >= 0 && y < n && y >= 0)
    {
        if (board[x][y] != 0)
            return 1; // Spot has already been taken

        board[x][y] = currMove; // Place current move
        moves.push(make_tuple(currMove, x, y)); // Add move to stack
        --movesLeft; // Reduce number of moves left
        (currMove == 'O') ? currMove = 'X' : currMove = 'O'; // Flip to next player
        return 0;
    }

    return 1;
}

// Undoes the last move, if any exist
void mnkSolver::undoMove()
{
    if (moves.empty())
    {
        cout << "No moves played." << endl;
        return; // No moves left to undo
    }

    char player = get<0>(moves.top()); // Get last move's player name
    int x = get<1>(moves.top()); // Get last move's x
    int y = get<2>(moves.top()); // Get last move's y

    board[x][y] = 0; // Reset the board position to 0
    currMove = player; // Flip to last player
    ++movesLeft; // Increase number of moves left
    moves.pop(); // Remove move from stack
}

// Prints the formatted board
void mnkSolver::printBoard()
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (board[i][j] != 0)
                cout << board[i][j];
            else
                cout << " ";
            if(j != n - 1)
                cout << "|";
        }
        cout << endl;
        for (int k = 0; k < (m * 2) - 1; ++k)
            cout << "-"; // Print one '-' per board slot and one per barrier '|'
        cout << endl;
    }
}

// Checks if a winner exists after the last move
char mnkSolver::checkWinner()
{
    if (moves.empty())
        return 0; // No moves yet
    char player = get<0>(moves.top()); // Get last move's player name
    int x = get<1>(moves.top()); // Get last move's x
    int y = get<2>(moves.top()); // Get last move's y

    int count = 0; // Number in a row

    for (int i = x; i < m; ++i) // Check horizontal
    {
        if (board[i][y] == player)
            count++;
        else
            break;
    }
    for (int i = x - 1; i >= 0; --i) // Don't double count current pos
    {
        if (board[i][y] == player)
            count++;
        else
            break;
    }

    if (count >= k)
        return player;
    count = 0; // Reset count

    for (int j = y; j < n; ++j) // Check vertical
    {
        if (board[x][j] == player)
            count++;
        else
            break;
    }
    for (int j = y - 1; j >= 0; --j) // Don't double count current pos
    {
        if (board[x][j] == player)
            count++;
        else
            break;
    }

    if (count >= k)
        return player;
    count = 0; // Reset count

    for (int i = x, j = y; i < m && j < n; ++i, ++j) // Check diagonal
    {
        if (board[i][j] == player)
            count++;
        else
            break;
    }
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j) // Don't double count current pos
    {
        if (board[i][j] == player)
            count++;
        else
            break;
    }

    if (count >= k)
        return player;
    
    if (movesLeft == 0)
        return 'T'; // Game is a tie
    return 0;
}

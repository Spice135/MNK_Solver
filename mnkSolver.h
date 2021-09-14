/******************************************************************************/
/*!
\file   mnkSolver.h
\date   09/13/2021
*/
/******************************************************************************/
#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <tuple>

using namespace std;

class mnkSolver
{
private:
  int m;  // x-dimension of the board
  int n;  // y-dimension of the board
  int k;  // Number needed in a row to win
  char currMove;  // Current Player
  int movesLeft;  // Number of moves left to play
  vector<vector<char>> board; // Game board
  stack<tuple<char, int, int>> moves; // Stack of moves
public:
	mnkSolver(int _m, int _n, int _k);
	int addMove(string input);
	void undoMove();
	void printBoard();
	char checkWinner();
	char getPlayer() { return currMove; };
};

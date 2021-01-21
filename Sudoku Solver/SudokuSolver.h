//	Program Name:		Sudoku Program Solver
//	Programmer Name:	Husam Alsheikh
//	Description:		Program utilizing backtracking algorithim to solve sudoku puzzle
//	Date Created:		08/08/2020

#pragma once
#include <iostream>

using namespace std;

#define size 9

class SudokuSolver {
private:
	int hints = 0;
	int solveTime = 0;
	int runTime = 0;
	int comparisons = 0;
	int actions = 0;
		
public:
	void createBoard();

	bool solveBoard(int board[size][size], int& actions);

	bool inCol(int board[size][size], int col, int num);

	bool inRow(int board[size][size], int row, int num);

	bool inSub(int board[size][size], int startRow, int startCol, int num);

	bool isValid(int board[size][size], int row, int col, int num);

	bool findEmpty(int board[size][size], int& row, int& col);

	void printBoard(int board[size][size]);

	void printFile(ofstream& output, int board[size][size]);

	void printMetrics();
};

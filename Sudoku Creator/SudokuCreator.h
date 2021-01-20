//	Program Name:		Sudoku Program Creator
//	Programmer Name:	Husam Alsheikh
//	Description:		Program utilizing backtracking algorithim from sudoku solver to create sudoku puzzle
//	Date Created:		08/08/2020

#pragma once
#include <iostream>
#include <fstream>
#include "D:\Projects\CIS 3501\CIS 3501\SudokuSolver\SudokuSolver.h"

using namespace std;

#define size 9

class SudokuCreator {
private:
	int board[size][size];
	int slnBoard[size][size];
	int gridPos[81];
	int guessNum[9];
	int difficulty;
	int start, end;

	//	Metrics to see how efficient the program runs
	int hints;			//	Metric 1	Number of hints
	int puzzleTime;		//	Metric 2	Time it took to create puzzle
	int numComparisons;	//	Metric 3	Number of number comparisons to location
	int actions;		//	Metric 4	Number of backtracking actions it took
	int timeToSolve;	//	Metric 5	Time to solve board

	SudokuSolver solver;
	ofstream output;
	ofstream puzzleOutput;
	string filePath;

public:
	SudokuCreator();

	void startSudoku();

	void fillBoard();

	void createBoard();

	void printBoard();

	void iterativeOutput();

	bool checkBox(int board[size][size], int startRow, int startCol, int num);

	bool fillRemaining(int row, int col);

	void extractPuzzle();
};
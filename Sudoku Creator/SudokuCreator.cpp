//	Program Name:		Sudoku Program Creator
//	Programmer Name:	Husam Alsheikh
//	Description:		Program utilizing backtracking algorithim from sudoku solver to create sudoku puzzle
//	Date Created:		08/08/2020

#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>
#include <string>
#include <iomanip>
#include <fstream>
#include "SudokuCreator.h"
#include "D:\Projects\CIS 3501\CIS 3501\SudokuSolver\SudokuSolver.h"

//	Description:	Constructor function that initializes board, and randomizes numbers for arrays
//	Pre-Condition:	none
//	Post-Condition:	Initializes board and randomizes numbers for arrays
SudokuCreator::SudokuCreator() {
	srand(time(NULL));

	//	Some initializations
	hints = 81;
	difficulty = 0;
	numComparisons = 0;
	start = 0;
	end = 0;
	puzzleTime = 0;
	numComparisons = 0;
	timeToSolve = 0;

	//	Initialize all board values to null
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			board[row][col] = NULL;
		}
	}

	//	Randomize grid
	for (int x = 0; x < 81; x++)
	{
		this->gridPos[x] = x;
	}
	random_shuffle(gridPos, (gridPos + 81));

	//	Randomize guessNum
	for (int x = 0; x < 9; x++)
	{
		this->guessNum[x] = x + 1;
	}
	random_shuffle(guessNum, (guessNum + 9));
}

//	Description:	Member function that runs most of the program
//	Pre-Condition:	none
//	Post-Condition:	calls most other functions to generate puzzle and print output
void SudokuCreator::startSudoku() {
	//	File to output sudoku puzzle for solver
	puzzleOutput.open("puzzleOutput.dat", ios::out);

	cout << "\t\tSudoku Puzzle Creator" << endl;

	cout << "Enter output file path: ";
	getline(cin, filePath);

	output.open(filePath, ios::out);

	//	Output to screen
	cout << "\n -\tEasy Difficulty,"<< setw(15) << "37 hints" << endl;
	cout << " -\tNormal Difficulty," << setw(13) << "27 hints" << endl;
	cout << " - \tHard Difficulty," << setw(15) << "17 hints" << endl;
	cout << "Choose level of difficulty (enter number of hints): ";
	cin >> difficulty;

	while (difficulty != 17 && difficulty != 27 && difficulty != 37) {	//	Validating difficulty level is in range
		cout << "Choose one of the three difficulty levels: ";
		output << "Choose one of the three difficulty levels: ";
		cin >> difficulty;
	}

	//	Output to file
	output << "\n -\tEasy Difficulty," << setw(15) << "37 hints" << endl;
	output << " -\tNormal Difficulty," << setw(13) << "27 hints" << endl;
	output << " - \tHard Difficulty," << setw(15) << "17 hints" << endl;
	output << "Choose level of difficulty (enter number of hints): " << endl;;
	output << "User enters: " << difficulty;
	
	//	Fill board with random numbers
	fillBoard();

	//	Print board
	cout << "\n\tInitial randomized board with no hints" << endl;
	output << "\n\tInitial randomized board with no hints" << endl;

	printBoard();
	solver.printFile(output, board);

	//	Create puzzle by taking out numbers to form hints
	start = clock();
	createBoard();
	end = clock();

	puzzleTime = end - start;

	cout << "\n\tSudoku Puzzle" << endl;
	output << "\n\tSudoku Puzzle" << endl;

	printBoard();
	solver.printFile(output, board);

	//	Extract hints to create data file for solver
	extractPuzzle();

	cout << "\n\n\tProgram Metrics" << endl;
	cout << "Number of hints: \t\t" << hints << endl;
	cout << "Time it took to create puzzle: \t" << puzzleTime << endl;
	cout << "Number of comparisons: \t\t" << numComparisons << endl;
	cout << "Number of backtracking actions: " << actions << endl;
	cout << "Time it took to solve board: \t" << timeToSolve << endl;

	output << "\n\n\tProgram Metrics:" << endl;
	output << "Number of hints: \t\t" << hints << endl;
	output << "Time it took to create puzzle: \t" << puzzleTime << endl;
	output << "Number of comparisons: \t\t" << numComparisons << endl;
	output << "Number of backtracking actions: " << actions << endl;
	output << "Time it took to solve board: \t" << timeToSolve << endl;

	output.close();
	puzzleOutput.close();
}

//	Description:	Member funciton that fills board with numbers, calls fillsRemaining
//	Pre-Condition:	none
//	Post-Condition:	Fills board with numbers
void SudokuCreator::fillBoard() {
	//	fill diagonal
	for (int x = 0; x < size; x += 3) {
		int num;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				do
				{
					num = rand() % 9 + 1;
				} while (checkBox(board, x, x, num));

				board[x + i][x + j] = num;
			}
		}
	}

	fillRemaining(0, 3);
}

//	Description:	Member function that removes numbers from board to leave hints in to generate puzzle
//	Pre-Condition:	none
//	Post-Condition:	Generates puzzle by removing numbers from already randomized board
void SudokuCreator::createBoard() {
	int count = 81 - difficulty;
	while (count != 0) {
		int z = rand() % 81;

		int i = (z / size);
		int j = z % size;
		if (j != 0)
			j = j - 1;

		if (board[i][j] != 0)
		{
			count--;
			hints--;
			board[i][j] = NULL;
		}
	}

	iterativeOutput();

	int tempBoard[size][size];
	memcpy(tempBoard, board, 81 * sizeof(float));
	start = clock();
	if (!solver.solveBoard(tempBoard, actions)) {
		end = clock();
		timeToSolve = end - start;

		fillBoard();
		createBoard();
	}

	solver.printBoard(tempBoard);
}

//	Description:	Member function that calls function from solver program to print board
//	Pre-Condition:	none
//	Post-Condition:	Calls print function from solver program to print board
void SudokuCreator::printBoard() {
	solver.printBoard(this->board);	//	Call print function from solver code (re-using my partners code)
}

//	Description:	Member function to print iterative output
//	Pre-Condition:	none
//	Post-Condition:	Iteratively prints board
void SudokuCreator::iterativeOutput() {
	cout << "\tIterative Output" << endl;
	output << "\tIterative Output" << endl;

	cout << "Row\tCol\tNum" << endl;
	output << "Row\tCol\tNum" << endl;

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {	//	Printing data
			if (board[row][col] == NULL) {
				cout << row << "\t" << col << "\t" << "0 " << endl;
				output << row << "\t" << col << "\t" << "0 " << endl;
			}
			else {
				cout << row << "\t" << col << "\t" << board[row][col] << " " << endl;
				output << row << "\t" << col << "\t" << board[row][col] << " " << endl;
			}
		}
	}
}

//	Description:	Member functiont that checks if found in box
//	Pre-Condition:	Board, starting row, starting column, the number
//	Post-Condition:	Returns true if found in box, false otherwise
bool SudokuCreator::checkBox(int board[size][size], int startRow, int startCol, int num) {
	return solver.inSub(board, startRow, startCol, num);	//	Calling inSub (re-using partner code)
}

//	Description:	Recursive member function that fills in remaining spaces in board
//	Pre-Condition:	row and column
//	Post-Condition:	Fills in remaining spaces in board
bool SudokuCreator::fillRemaining(int row, int col) {
	if (col >= size && row < size - 1)
	{
		row = row + 1;
		col = 0;
	}
	if (row >= size && col >= size)
		return true;

	if (row < 3)
	{
		if (col < 3)
			col = 3;
	}
	else if (row < size - 3)
	{
		if (col == (int)(row / 3) * 3)
			col = col + 3;
	}
	else
	{
		if (col == size - 3)
		{
			row = row + 1;
			col = 0;
			if (row >= size)
				return true;
		}
	}

	if (row < 0 || col < 0 || col > 8 || row > 8) {
		return false;
	}

	for (int num = 1; num <= size; num++)
	{
		if (solver.isValid(board, row, col, num))	//	Calling isValid (re-using partner code)
		{
			numComparisons++;

			board[row][col] = num;
			if (fillRemaining(row, col + 1))
				return true;

			board[row][col] = NULL;
		}
	}

	return false;
}

//	Description:	Member function that extracts data from board and prints to data file as input file for solver
//	Pre-Condition:	none
//	Post-Condition:	Prints board with hints to file
void SudokuCreator::extractPuzzle() {
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {	//	Printing data
			if (board[row][col] == NULL) {
				puzzleOutput << row << " " << col << " " << "0 " << endl;
			}
			else {
				puzzleOutput << row << " " << col << " " << board[row][col] << " " << endl;
			}
		}
	}
}
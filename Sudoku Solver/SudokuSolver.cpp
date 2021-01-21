//	Program Name:		Sudoku Program Solver
//	Programmer Name:	Husam Alsheikh
//	Description:		Program utilizing backtracking algorithim to solve sudoku puzzle
//	Date Created:		08/08/2020

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "SudokuSolver.h"

using namespace std;

//	Description:	
//	Pre-Condition:	
//	Post-Condition:	
void SudokuSolver::createBoard() {
	int board[size][size];
	ifstream input;
	string filePath;
	string line;
	int row, col, num;
	int start, end;
	int solveStart, solveEnd;

	start = clock();

	cout << "Enter filepath for input file: ";
	getline(cin, filePath);

	ifstream temp(filePath);
	if (!temp.good()) {	//	Making sure outputting to existing file
		cout << "\n\n\tInvalid file path, Exiting program" << endl;
		exit(0);
	}
	else if (temp.peek() == ifstream::traits_type::eof()) {
		cout << "\n\n\tFile is empty, Exiting program" << endl;
		exit(0);
	}

	input.open(filePath);

	while (!input.eof()) {
		string temp;

		getline(input, line);

		if (line == "") {
			break;
		}

		istringstream iss(line);

		iss >> temp;
		row = stoi(temp);

		iss >> temp;
		col = stoi(temp);

		iss >> temp;
		num = stoi(temp);

		board[row][col] = num;

		if (board[row][col] != 0) {
			hints++;
		}
	}

	cout << "Input board" << endl;
	printBoard(board);

	solveStart = clock();

	solveBoard(board, actions);

	solveEnd = clock();
	solveTime = solveEnd - solveStart;

	cout << "Solved Board" << endl;
	printBoard(board);

	printMetrics();

	input.close();

	end = clock();

	runTime = end - start;
}

//	Description:	
//	Pre-Condition:	
//	Post-Condition:	
bool SudokuSolver::solveBoard(int board[size][size], int& actions) {
	int row, col;

	if (!findEmpty(board, row, col)) {	//	As board is full
		return true;
	}

	for (int x = 1; x <= size; x++) {	//	Else backtracking to solve
		if (isValid(board, row, col, x)) {
			board[row][col] = x;

			if (solveBoard(board, actions)) {
				actions++;
				return true;
			}

			board[row][col] = NULL;
		}
	}

	return false;
}

//	Description:	
//	Pre-Condition:	
//	Post-Condition:	
bool SudokuSolver::inRow(int board[size][size], int row, int num) {
	for (int col = 0; col < size; col++) {
		if (board[row][col] == num) {	//	If found return true
			return true;
		}
	}

	return false;
}

//	Description:	
//	Pre-Condition:	
//	Post-Condition:	
bool SudokuSolver::inCol(int board[size][size], int col, int num) {
	for (int row = 0; row < size; row++) {
		if (board[row][col] == num) {	//	If found return true;
			return true;
		}
	}

	return false;
}

//	Description:	
//	Pre-Condition:	
//	Post-Condition:	
bool SudokuSolver::inSub(int board[size][size], int startRow, int startCol, int num) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board[row + startRow][col + startCol] == num) {	//	If found return true
				return true;
			}
		}
	}

	return false;
}

//	Description:	
//	Pre-Condition:	
//	Post-Condition:	
bool SudokuSolver::isValid(int board[size][size], int row, int col, int num) {
	comparisons++;

	//	If not found in row, column or subGroup
	return !inRow(board, row, num) && !inCol(board, col, num) && !inSub(board, row - row % 3, col - col % 3, num) && board[row][col] == NULL;
}

//	Description:	
//	Pre-Condition:	
//	Post-Condition:	
bool SudokuSolver::findEmpty(int board[size][size], int& row, int& col) {
	for (row = 0; row < size; row++) {
		for (col = 0; col < size; col++) {
			if (board[row][col] == NULL) {	//	If empty return true
				return true;
			}
		}
	}
	return false;
}

//	Description:	
//	Pre-Condition:	
//	Post-Condition:	
void SudokuSolver::printBoard(int board[size][size]) {
	cout << "--------------------------" << endl;

	for (int row = 0; row < size; row++) {
		cout << "|";

		for (int col = 0; col < size; col++) {
			if (col == 3 || col == 6) {
				cout << " | ";
			}

			if (board[row][col] == NULL) {
				cout << "  ";
			}
			else {
				cout << board[row][col] << " ";
			}
		}

		cout << "|";

		if (row == 2 || row == 5) {
			cout << endl;

			cout << "|------------------------|";
		}

		cout << endl;
	}

	cout << "--------------------------" << endl;
}

//	Description:	
//	Pre-Condition:	
//	Post-Condition:	
void SudokuSolver::printFile(ofstream& output, int board[size][size]) {
	output << "--------------------------" << endl;

	for (int row = 0; row < size; row++) {
		output << "|";

		for (int col = 0; col < size; col++) {
			if (col == 3 || col == 6) {
				output << " | ";
			}

			if (board[row][col] == NULL) {
				output << "  ";
			}
			else {
				output << board[row][col] << " ";
			}
		}

		output << "|";

		if (row == 2 || row == 5) {
			output << endl;

			output << "|------------------------|";
		}

		output << endl;
	}

	output << "--------------------------" << endl;
}

//	Description:
//	Pre-Condition:	
//	Post-Condition:	
void SudokuSolver::printMetrics() {
	cout << "\tMetrics" << endl;
	cout << "1. Number of hints: \t\t\t" << hints << endl;
	cout << "2. Number of backtracking actions: \t" << actions << endl;
	cout << "3. Number of comparisons: \t\t" << comparisons << endl;
	cout << "4. Time to solve puzzle: \t\t" << solveTime << endl;
	cout << "5. Time to run program: \t\t" << runTime << endl;
}

//  Project Identifier: N/A
//              Author: Vishal Nayak
//             Project: Sudoku Solver
//              Module: driver.cpp
//         Description: Reads in Sudoku Grid
//

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Grid.h"
#include "solver.h"

using namespace std;

const string IN = ".in";
const string OUT = ".out";
const string CORRECT = ".correct";
const string PATHNAME = "/Users/vrnayak/Desktop/Coding/Personal/Sudoku Solver/Sudoku Grids/grid";

const int NUM_GRIDS = 2;

void printInfo();
bool fileComp(string fileName1, string fileName2);
bool ASSERT_TRUE(bool statement) {
	
	if (statement) return true;
	else exit(3);
}

int main() {
	
	printInfo();
	for (int i = 1; i <= NUM_GRIDS; ++i) {
		
		string fileIn = PATHNAME + to_string(i) + IN;
		string fileOut = PATHNAME + to_string(i) + OUT;
		string fileCorrect = PATHNAME + to_string(i) + CORRECT;
		
		ifstream inputStream(fileIn);
		ofstream outputStream(fileOut);
		
		Grid sudokuGrid(inputStream);
		
		cout << "Sudoku Grid #" << i << "\n"
			 << "# of Empty Cells: "
			 << sudokuGrid.numEmptyCells() << "\n";
		
		clock_t start;
		double time;
		
		start = std::clock();
		bruteForceSolve(sudokuGrid);
		time = (std::clock() - start) / (double) CLOCKS_PER_SEC;
		sudokuGrid.print(outputStream);
		ASSERT_TRUE(fileComp(fileOut, fileCorrect));
		cout << "Time taken to solve: " << time << "s\n";
		cout << endl;
	}
	return 0;
} // main()

void printInfo() {
	
	cout << "Sudoku Solver Program\n"
		 << "# of Grids to Solve: " << NUM_GRIDS
		 << endl << endl;
}

bool fileComp(string fileName1, string fileName2) {
	
	ifstream file1(fileName1), file2(fileName2);
	
	int cell1, cell2;
	vector<int> grid;
	grid.reserve(81);
	
	while (file1 >> cell1)
		grid.push_back(cell1);

	int counter = 0;
	while (file2 >> cell2) {
		if (grid[counter++] != cell2)
			return false;
	} // while
	return counter == 81;
}

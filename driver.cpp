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
const string PATHNAME = "/Users/vrnayak/Desktop/Coding/Personal"
						"/Sudoku Solver/Sudoku Grids/grid";
const int NUM_GRIDS = 2;

void printInfo();
bool fileComp(string fileName1, string fileName2);
void solve(Grid &sudokuGrid, string fileOut, string fileCorrect);
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
		Grid sudokuGrid(inputStream);
		
		cout << "Sudoku Grid #" << i << "\n";
		solve(sudokuGrid, fileOut, fileCorrect);
	} // for...i
	return 0;
} // main()

void printInfo() {
	
	cout << "Sudoku Solver Program\n"
		 << "# of Grids to Solve: " << NUM_GRIDS
		 << endl << endl;
} // printInfo()

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
} // fileComp()

void solve(Grid &sudokuGrid, string fileOut, string fileCorrect) {
	
	clock_t start;
	double smartTime = 0.0, simpleTime = 0.0, forceTime = 0.0;
	int smartCells = 0, simpleCells = 0, forceCells = 0;
	int emptyCells = 81;
	
	cout << "# of Empty Cells: "
		 << sudokuGrid.numEmptyCells() << "\n";
	
	while (emptyCells > sudokuGrid.numEmptyCells()) {
		
		emptyCells = sudokuGrid.numEmptyCells();
		start = std::clock();
		smartSolve(sudokuGrid);
		smartTime = (std::clock() - start) / (double) CLOCKS_PER_SEC;
		smartCells += emptyCells - sudokuGrid.numEmptyCells();
		/*
		emptyCells = sudokuGrid.numEmptyCells();
		start = std::clock();
		simpleSolve(sudokuGrid);
		simpleTime = (std::clock() - start) / (double) CLOCKS_PER_SEC;
		simpleCells += emptyCells - sudokuGrid.numEmptyCells();
		 */
	} // while
	
	start = std::clock();
	bruteForceSolve(sudokuGrid);
	forceTime = (std::clock() - start) / (double) CLOCKS_PER_SEC;
	forceCells = emptyCells;
	
	ofstream os(fileOut);
	sudokuGrid.print(os);
	ASSERT_TRUE(fileComp(fileOut, fileCorrect));
	
	cout << "SmartSolve:\t Filled " << smartCells << " cells in "
		 << smartTime << " seconds\n"
		 << "SimpleSolve: Filled " << simpleCells << " cells in "
		 << simpleTime << " seconds\n"
		 << "Brute Force: Filled " << forceCells << " cells in "
		 << forceTime << " seconds\n"
		 << "Total Time Taken: " << smartTime + simpleTime + forceTime
		 << "s\n" << endl;
} // solve()

//  Project Identifier: N/A
//              Author: Vishal Nayak
//             Project: Sudoku Solver
//              Module: driver.cpp
//         Description: Reads in Sudoku Grid
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Grid.h"
#include "solver.h"

using namespace std;

const string PATHNAME = "/Users/vrnayak/Desktop/Coding/Personal/Sudoku Solver/Sudoku Grids/";

bool fileComp(string fileName1, string fileName2);

int main() {
	
	ifstream gridIn(PATHNAME + "grid1.in");
	ofstream gridOut(PATHNAME + "grid1.out");
	Grid sudokuGrid(gridIn);
	
	bruteForceSolve(sudokuGrid);
	sudokuGrid.print(gridOut);
	if (fileComp(PATHNAME + "grid1.out",
				 PATHNAME + "grid1.correct"))
		cout << "Success!" << endl;
	
	return 0;
	
} // main()

bool fileComp(string fileName1, string fileName2) {
	
	ifstream file1(fileName1);
	ifstream file2(fileName2);
	
	int cell1, cell2;
	vector<int> grid;
	grid.reserve(81);
	
	while (file1 >> cell1) {
		grid.push_back(cell1);
	} // while
	
	int counter = 0;
	while (file2 >> cell2) {
		if (grid[counter++] != cell2)
			return false;
	} // while
	return true;
}

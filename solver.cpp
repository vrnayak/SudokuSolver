//  Project Identifier: N/A
//              Author: Vishal Nayak
//             Project: Sudoku Solver
//              Module: solver.cpp
//         Description: Sudoku Solver Algorithms Implementation
//

#include <iostream>
#include "solver.h"

using namespace std;

// EFFECTS: Performs brute force solving algorithm on sudoku grid
void bruteForceSolve(Grid &grid) {
	
	int cell = grid.findFirstEmptyCell();
	if (cell == -1) return;
	
	for (int i = 1; i <= 9; ++i) {
		
		if (grid.checkIfValid(grid.getRow(cell), grid.getCol(cell), i)) {
			grid.set(grid.getRow(cell), grid.getCol(cell), i);
			bruteForceSolve(grid);
			if (grid.findFirstEmptyCell() == -1) break;
		} // if...else
	} // for...i
	if (grid.findFirstEmptyCell() != -1)
		grid.set(grid.getRow(cell), grid.getCol(cell), 0);
} // bruteForceSolve()

// EFFECTS: Performs simple process of elimination algorithm to fill in cells
void simpleSolve(Grid &sudokuGrid) {
	
	
} // simpleSolve()

// EFFECTS: Performs basic algorithm utilized by humans to solve sudokus
void smartSolve(Grid &sudokuGrid) {
	
} // smartSolve()



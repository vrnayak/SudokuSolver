//  Project Identifier: N/A
//              Author: Vishal Nayak
//             Project: Sudoku Solver
//              Module: solver.cpp
//         Description: Sudoku Solver Algorithms Implementation
//

#include <algorithm>
#include <iostream>
#include <numeric>
#include "solver.h"

using namespace std;

// EFFECTS: Performs brute force solving algorithm on sudoku grid
void bruteForceSolve(Grid &grid) {
	
	if (grid.isFilled()) return;
	
	int cell = grid.findFirstEmptyCell();
	for (int i = 1; i <= 9; ++i) {
		
		if (grid.checkIfValid(grid.getRow(cell), grid.getCol(cell), i)) {
			
			grid.set(grid.getRow(cell), grid.getCol(cell), i);
			bruteForceSolve(grid);
			if (grid.isFilled()) break;
		} // if...else
	} // for...i
	if (!grid.isFilled())
		grid.set(grid.getRow(cell), grid.getCol(cell), 0);
} // bruteForceSolve()

// EFFECTS: Performs simple process of elimination algorithm to fill in cells
void simpleSolve(Grid &grid) {
	
	if (grid.isFilled()) return;
	for (int index = 0; index < 81; ++index) {
		
		if (grid.at(grid.getRow(index), grid.getCol(index)) == 0) {
			
			vector<int> validNums;
			validNums.reserve(9);
			
			for (int i = 1; i <= 9; ++i) {
				if (grid.checkIfValid(grid.getRow(index), grid.getCol(index), i))
					validNums.push_back(i);
			} // for...i
			
			if (validNums.size() == 1) {
				grid.set(grid.getRow(index), grid.getCol(index), validNums[0]);
			} // if...else
		} // if...else
	} // for...index
} // simpleSolve()

// EFFECTS: Performs basic algorithm utilized by humans to solve sudokus
void smartSolve(Grid &grid) {
	
	if (grid.isFilled()) return;
	
	
	
} // smartSolve()

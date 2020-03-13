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
void simpleSolve(Grid &grid) {
	
	for (int index = 0; index < 81; ++index) {
		
		vector<int> nums(9);
		iota(nums.begin(), nums.end(), 1);
		
		if (grid.at(grid.getRow(index), grid.getCol(index)) == 0) {
			
			for (int i = 1; i <= 9; ++i) {
				if (!grid.checkIfValid(grid.getRow(index), grid.getCol(index), i))
					nums[i] = 0;
			} // for...i
			
			if (count(nums.begin(), nums.end(), 0) == 8) {
				for (int j = 0; j < 9; ++j) {
					if (nums[j] != 0) {
						grid.set(grid.getRow(index), grid.getCol(index), nums[j]);
						break;
					} // if...else
				} // for...j
			} // if...else
		} // if...else
	} // for...index
} // simpleSolve()

// EFFECTS: Performs basic algorithm utilized by humans to solve sudokus
void smartSolve(Grid &grid) {
	
} // smartSolve()



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
	
	for (int index = 0; index < 81; ++index) {
		
		if (grid.at(grid.getRow(index), grid.getCol(index)) == 0) {
			
			vector<int> validNums(9), unavailable, possible;
			iota(validNums.begin(), validNums.end(), 1);
			unavailable.reserve(9);
			
			for (int col = 0; col < 9; ++col) {
				if (grid.at(grid.getRow(index), col) != 0)
					unavailable.push_back(grid.at(grid.getRow(index), col));
			} // for...col
			
			for (int row = 0; row < 9; ++row) {
				if (grid.at(row, grid.getCol(index)) != 0)
					unavailable.push_back(grid.at(row, grid.getCol(index)));
			} // for...row
			
			for (int rowDiff = 0; rowDiff < 3; ++rowDiff) {
				for (int colDiff = 0; colDiff < 3; ++colDiff) {
					int val = grid.at(rowDiff + 3 * (grid.getBox(index) / 3),
									  colDiff + 3 * (grid.getBox(index) % 3));
					if (val != 0)
						unavailable.push_back(val);
				} // for...colDiff
			} // for...rowDiff
			
			if (unavailable.size() == 8) {
				
				int val = 45 - accumulate(unavailable.begin(), unavailable.end(), 0);
				grid.set(grid.getRow(index), grid.getCol(index), val);
			} // if...else
		} // if...else
	} // for...index
} // smartSolve()

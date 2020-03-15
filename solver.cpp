//  Project Identifier: 490395975692179385863
//              Author: Vishal Nayak
//             Project: Sudoku Solver
//              Module: solver.cpp
//         Description: Sudoku Solver Algorithms Implementation
//

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include "solver.h"

using namespace std;

static const int NUMS = 9;
static const int NUM_ROWS = 9;
static const int NUM_COLS = 9;
static const int GRID_SIZE = NUM_ROWS * NUM_COLS;

// EFFECTS: Performs brute force solving algorithm on sudoku grid
void bruteForceSolve(Grid &grid) {
	
	if (grid.isFilled()) return;
	
	int cell = grid.findFirstEmptyCell();
	for (int i = 1; i <= NUMS; ++i) {
		
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
	for (int index = 0; index < GRID_SIZE; ++index) {
		
		if (grid.at(grid.getRow(index), grid.getCol(index)) == 0) {
			
			vector<int> validNums;
			validNums.reserve(NUMS);
			
			for (int i = 1; i <= NUMS; ++i) {
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
	
	for (int index = 0; index < GRID_SIZE; ++index) {
		
		if (grid.at(grid.getRow(index), grid.getCol(index)) == 0) {
			
			vector<int> unavailable;
			unavailable.reserve(3 * NUMS); // row, col, and box
			
			for (int col = 0; col < NUM_COLS; ++col) {
				if (grid.at(grid.getRow(index), col) != 0)
					unavailable.push_back(grid.at(grid.getRow(index), col));
			} // for...col
			
			for (int row = 0; row < NUM_ROWS; ++row) {
				if (grid.at(row, grid.getCol(index)) != 0)
					unavailable.push_back(grid.at(row, grid.getCol(index)));
			} // for...row
			
			for (int rowDiff = 0; rowDiff < sqrt(NUM_ROWS); ++rowDiff) {
				for (int colDiff = 0; colDiff < sqrt(NUM_COLS); ++colDiff) {
					int val = grid.at(rowDiff + 3 * (grid.getBox(index) / 3),
									  colDiff + 3 * (grid.getBox(index) % 3));
					if (val != 0)
						unavailable.push_back(val);
				} // for...colDiff
			} // for...rowDiff
			
			sort(unavailable.begin(), unavailable.end());
			auto endIter = unique(unavailable.begin(), unavailable.end());
			
			if (endIter == unavailable.begin() + NUMS - 1) {
				
				int val = 45 - accumulate(unavailable.begin(),
										  endIter, 0);
				grid.set(grid.getRow(index), grid.getCol(index), val);
			} // if...else
		} // if...else
	} // for...index
} // smartSolve()

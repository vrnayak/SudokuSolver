//  Project Identifier: 490395975692179385863
//              Author: Vishal Nayak
//             Project: Sudoku Solver
//              Module: Grid.cpp
//         Description: Grid Class Implementation
//

#include <cmath>
#include <iostream>
#include "Grid.h"

using namespace std;


// EFFECTS: Initializes a 9x9 grid object and fills it with 0's
Grid::Grid() {
    
    for (int row = 0; row < NUM_ROWS; ++row) {
        for (int col = 0; col < NUM_COLS; ++col) {
            set(row, col, 0);
        } // for...col
    } // for...row
} // Grid()

// EFFECTS: Initializes a 9x9 grid object from given input stream
Grid::Grid(istream &is) {
    
    int cellNum;
    for (int row = 0; row < NUM_ROWS; ++row) {
        for (int col = 0; col < NUM_COLS; ++col) {
            is >> cellNum;
            set(row, col, cellNum);
        } // for...col
    } // for...row
} // Grid()

// EFFECTS: Returns the value at given row & column
int Grid::at(int row, int col) const { return grid[row][col]; }

// EFFECTS: Returns row of cell with given index
int Grid::getRow(int index) const { return index / NUM_COLS; }

// EFFECTS: Returns column of cell with given index
int Grid::getCol(int index) const { return index % NUM_COLS; }

// EFFECTS: Returns box of cell with given index
int Grid::getBox(int index) const {
    
	if (index % NUM_COLS == 0 ||
		index % NUM_COLS == 1 ||
		index % NUM_COLS == 2)
		return 0 + 3 * (index / 27);
	
	else if (index % NUM_COLS == 3 ||
			 index % NUM_COLS == 4 ||
			 index % NUM_COLS == 5)
		return 1 + 3 * (index / 27);
	
	else if (index % NUM_COLS == 6 ||
			 index % NUM_COLS == 7 ||
			 index % NUM_COLS == 8)
		return 2 + 3 * (index / 27);
	else
		return -1;
} // getBox()

// EFFECTS: Returns index of cell at given row and column
int Grid::getIndex(int row, int col) const { return (NUM_COLS * row + col); }

// EFFECTS: Fills in the cell at given row & column with given value
void Grid::set(int row, int col, int value) { grid[row][col] = value; }

// EFFECTS: Checks whether setting (rowCheck, colCheck) to value
//			results in a valid sudoku grid
bool Grid::checkIfValid(int rowCheck, int colCheck, int value) {
    
    set(rowCheck, colCheck, value);
    int cellIndex = getIndex(rowCheck, colCheck);
    int boxStartIndex = 27 * (getBox(cellIndex) / 3) +
						 3 * (getBox(cellIndex) % 3);
    
    if (getCount(value, cellIndex, "row") > 1 ||
        getCount(value, cellIndex, "col") > 1 ||
        getCount(value, boxStartIndex, "box") > 1) {
        
        set(rowCheck, colCheck, 0);
        return false;
    } // if...else
    
    set(rowCheck, colCheck, 0);
    return true;
} // checkIfValid()

// EFFECTS: Returns index of first empty cell in sudoku grid
int Grid::findFirstEmptyCell() const {
    
    for (int row = 0; row < NUM_ROWS; ++row) {
        for (int col = 0; col < NUM_COLS; ++col) {
            if (at(row, col) == 0)
				return getIndex(row, col);
        } // for...col
    } // for...row
    return -1;
} // findFirstEmptyCell()

// EFFECTS: Returns the number of empty cells
int Grid::numEmptyCells() const {
	
	int count = 0;
	for (int row = 0; row < NUM_ROWS; ++row) {
		for (int col = 0; col < NUM_COLS; ++col) {
			if (at(row, col) == 0)
				count++;
		} // for...col
	} // for...row
	return count;
} // numEmptyCells()

// EFFECTS: Returns whether the grid is filled or not
bool Grid::isFilled() const { return (findFirstEmptyCell() == -1); }

// EFFECTS: Prints sudoku grid to &os
void Grid::print(std::ostream &os) const {
    
    for (int row = 0; row < NUM_ROWS; ++row) {
		for (int col = 0; col < NUM_COLS; ++col) {
			os << at(row, col) << " ";
		} // for...col
        os << endl;
    } // for...row
} // print()

// EFFECTS: Returns number of occurrences of value in given region,
//          which is specfied by areaString ("row", "col", "box")
//          start refers to first cell in specified region
int Grid::getCount(int value, int start, std::string regionType) const {
    
    int count = 0;
    if (regionType == "row") {
        for (int col = 0; col < NUM_COLS; ++col) {
            if (at(getRow(start), col) == value)
				count++;
        } // for...col
		
    } else if (regionType == "col") {
        for (int row = 0; row < NUM_ROWS; ++row) {
            if (at(row, getCol(start)) == value)
				count++;
        } // for...row
		
    } else if (regionType == "box") {
        for (int rowDiff = 0; rowDiff < sqrt(NUM_ROWS); ++rowDiff) {
            for (int colDiff = 0; colDiff < sqrt(NUM_COLS); ++colDiff) {
                if (at(getRow(start) + rowDiff,
					   getCol(start) + colDiff) == value)
                    count++;
            } // for...colDiff
        } // for...rowDiff
    } // if...else
    return count;
} // getCount()

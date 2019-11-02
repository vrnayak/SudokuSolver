//
//  Project Name: Sudoku Solver
//  Created By: Vishal Nayak
//
//  OVERVIEW: Program completes a partially filled in sudoku grid
//
//  Module Name: sudoku.cpp
//  Module Description: Grid Class & Sudoku Function Implementations
//

#include <iostream>
#include "sudoku.h"

using namespace std;


// EFFECTS: Initializes a 9x9 grid object and fills it with 0's
Grid::Grid() {
    
    for (int row = 0; row < ROW_SIZE; ++row) {
        for (int col = 0; col < COL_SIZE; ++col) {
            set(row, col, 0);
        }
    }
}

// EFFECTS: Initializes a 9x9 grid object from given input stream
Grid::Grid(istream &is) {
    
    int cellNum;
    
    for (int row = 0; row < ROW_SIZE; ++row) {
        for (int col = 0; col < COL_SIZE; ++col) {
            is >> cellNum;
            set(row, col, cellNum);
        }
    }
}

// EFFECTS: Returns the value at given row & column
int Grid::at(int row, int col) const {
    
    return grid[row][col];
}

// EFFECTS: Returns row of cell with given index
int Grid::getRow(int index) const {
    
    return index / ROW_SIZE;
}

// EFFECTS: Returns column of cell with given index
int Grid::getCol(int index) const {
    
    return index % ROW_SIZE;
}

// EFFECTS: Returns index of cell at given row and column
int Grid::getIndex(int row, int col) const {
    
    return (9 * row + col);
}

// EFFECTS: Fills in the cell at given row & column with given value
void Grid::set(int row, int col, int value) {
    
    grid[row][col] = value;
}

bool Grid::checkIfValid(int rowCheck, int colCheck, int value) {
    
    set(rowCheck, colCheck, value);
    int cellIndex = getIndex(rowCheck, colCheck);
    int boxStartIndex = cellIndex - (cellIndex % 9);
    
    if (getCount(value, cellIndex, "row") > 1 ||
        getCount(value, cellIndex, "col") > 1 ||
        getCount(value, boxStartIndex, "box") > 1) {
        
        set(rowCheck, colCheck, 0);
        return false;
    }
    
    set(rowCheck, colCheck, 0);
    return true;
}

// EFFECTS: Returns index of first empty cell in sudoku grid
int Grid::findFirstEmptyCell() const {
    
    for (int row = 0; row < ROW_SIZE; ++row) {
        for (int col = 0; col < COL_SIZE; ++col) {
            if (at(row, col) == 0) {
                return static_cast<int>(&grid[row][col] - &grid[0][0]);
            }
        }
    }
    return -1;
}

// EFFECTS: Checks whether sudoku grid is correctly solved
bool Grid::validateGrid() const {
    
    
    return false;
    
}

// EFFECTS: Prints sudoku grid to &os
void Grid::print(std::ostream &os) const {
    
}

// EFFECTS: Returns number of occurrences of value in given region,
//          which is specfied by areaString ("row", "col", "box")
//          start refers to first cell in specified region
int Grid::getCount(int value, int start, std::string regionType) const {
    
    int count = 0;
    
    if (regionType == "row") {
        for (int col = 0; col < COL_SIZE; ++col) {
            if (at(getRow(start), col) == value) {
                count++;
            }
        }
        return count;
        
    } else if (regionType == "col") {
        for (int row = 0; row < ROW_SIZE; ++row) {
            if (at(row, getCol(start)) == value) {
                count++;
            }
        }
        return count;
        
    } else if (regionType == "box") {
        for (int rowDiff = 0; rowDiff < 3; ++rowDiff) {
            for (int colDiff = 0; colDiff < 3; ++colDiff) {
                if (at(getRow(start) + rowDiff, getCol(start) + colDiff) == value) {
                    count++;
                }
            }
        }
        return count;
    }
    return -1;
}

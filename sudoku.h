//
//  Project Name: Sudoku Solver
//  Created By: Vishal Nayak
//
//  OVERVIEW: Program completes a partially filled in sudoku grid
//
//  Module Name: sudoku.h
//  Module Description: Grid Class & Sudoku Function Declarations
//

#ifndef sudoku_h
#define sudoku_h

#include <iostream>


class Grid {
public:
    
    // EFFECTS: Initializes a 9x9 grid object and fills it with 0's
    Grid();
    
    // REQUIRES: &is contains an open, properly formatted file
    // EFFECTS: Initializes a 9x9 grid object from given input stream
    Grid(std::istream &is);
    
    // REQUIRES: 0 <= row < 9 && 0 <= col < 9
    // EFFECTS: Returns the value at given row & column
    int at(int row, int col) const;
    
    // REQUIRES: 0 <= row < 9 && 0 <= col < 9 && 1 <= value <= 9
    // MODIFIES: grid
    // EFFECTS: Fills in the cell at given row & column with given value
    void set(int row, int col, int value);
    
    // EFFECTS: Returns index of first empty cell in sudoku grid
    int findFirstEmptyCell() const;
    
    // EFFECTS: Checks whether current sudoku grid is valid
    bool checkIfValid() const;
    
    // EFFECTS: Prints sudoku grid to &os
    void print(std::ostream &os) const;
    
private:
    
    static const int GRID_SIZE = 81;
    static const int ROW_SIZE = 9;
    static const int COL_SIZE = 9;
    int grid[GRID_SIZE];
    
    // EFFECTS: Checks whether cell position is valid
    bool checkValidCell(int row, int col) const;
};


// Sudoku Solving Algorithms

// REQUIRES: sudokuGrid points to a valid Grid
// MODIFIES: *sudokuGrid
// EFFECTS: Performs brute force solving algorithm on sudoku grid
void bruteForceSolve(Grid *sudokuGrid);

// REQUIRES: sudokuGrid points to a valid Grid
// MODIFIES: *sudokuGrid
// EFFECTS: Performs simple process of elimination algorithm to fill in cells
void simpleSolve(Grid *sudokuGrid);

// REQUIRES: sudokuGrid points to a valid Grid
// MODIFIES: *sudokuGrid
// EFFECTS: Performs basic algorithm utilized by humans to solve sudokus
void smartSolve(Grid *sudokuGrid);

#endif /* sudoku_h */

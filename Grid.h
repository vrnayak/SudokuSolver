//  Project Identifier: N/A
//              Author: Vishal Nayak
//             Project: Sudoku Solver
//              Module: Grid.h
//         Description: Grid Class Declaration
//

#ifndef Grid_h
#define Grid_h

#include <iostream>
#include <string>
#include <vector>


class Grid {
    
    // OVERVIEW: A 9x9 Sudoku Grid with basic access methods
    
public:
    
    // EFFECTS: Initializes a 9x9 grid object and fills it with 0's
    Grid();
    
    // REQUIRES: &is contains an open, properly formatted file
    // EFFECTS: Initializes a 9x9 grid object from given input stream
	Grid(std::istream &is);
    
    // REQUIRES: 0 <= row < 9 && 0 <= col < 9
    // EFFECTS: Returns the value at given row & column
    int at(int row, int col) const;
    
    // REQUIRES: index is less than GRID_SIZE
    // EFFECTS: Returns row of cell with given index
    int getRow(int index) const;
    
    // REQUIRES: index is less than GRID_SIZE
    // EFFECTS: Returns column of cell with given index
    int getCol(int index) const;
    
    // REQUIRES: index is less than GRID_SIZE
    // EFFECTS: Returns box of cell with given index
    int getBox(int index) const;
    
    // REQUIRES: 0 <= row < 9 && 0 <= col < 9
    // EFFECTS: Returns index of cell at given row and column
    int getIndex(int row, int col) const;
    
    // REQUIRES: 0 <= row < 9 && 0 <= col < 9 && 1 <= value <= 9
    // MODIFIES: grid
    // EFFECTS: Fills in the cell at given row & column with given value
    //          only if it would result in a valid sudoku grid
    void set(int row, int col, int value);
    
    // REQUIRES: 0 <= row < 9 && 0 <= col < 9 && 1 <= value <= 9
    // MODIFIES: grid
    // EFFECTS: Checks whether assigning cell at given row & column the
    //          the given value is a valid move
    bool checkIfValid(int row, int col, int value);
    
    // EFFECTS: Returns index of first empty cell in sudoku grid
    int findFirstEmptyCell() const;
    
    // EFFECTS: Prints sudoku grid to &os
	void print(std::ostream &os) const;
    
private:
    
    static const int GRID_SIZE = 81;
    static const int ROW_SIZE = 9;
    static const int COL_SIZE = 9;
	int grid[ROW_SIZE][COL_SIZE];
	
    // EFFECTS: Returns number of occurrences of value in given region,
    //          which is specfied by areaString ("row", "col", "box")
    //          start refers to first cell in specified region
    int getCount(int value, int start, std::string regionType) const;
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

#endif /* Grid_h */

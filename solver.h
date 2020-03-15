//  Project Identifier: 490395975692179385863
//              Author: Vishal Nayak
//             Project: Sudoku Solver
//              Module: solver.h
//         Description: Sudoku Solver Algorithms Declarations
//

#ifndef solver_h
#define solver_h

#include <iostream>
#include "Grid.h"

// REQUIRES: sudokuGrid points to a valid Grid
// MODIFIES: sudokuGrid
// EFFECTS: Performs brute force solving algorithm on sudoku grid
void bruteForceSolve(Grid &grid);

// REQUIRES: sudokuGrid points to a valid Grid
// MODIFIES: sudokuGrid
// EFFECTS: Performs process of elimination algorithm to fill in cells
void simpleSolve(Grid &grid);

// REQUIRES: sudokuGrid points to a valid Grid
// MODIFIES: sudokuGrid
// EFFECTS: Performs algorithm utilized by humans to solve sudokus
void smartSolve(Grid &grid);

#endif /* solver_h */

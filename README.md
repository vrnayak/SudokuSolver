# SudokuSolver
## Overview
The *SudokuSolver* program solves 9x9 sudoku puzzles by filling in the empty cells present in the grid. 

## Quick Start
```command-line
$ ./sudoku.exe [--info] [--file <filename>]
```
The `--info` flag is optional and results in the program giving detailed output regarding the time taken to complete the puzzle, including the time taken by each of the three algorithms. 

## Program Modes
The program has two modes. If the user supplies a file that contains a sudoku grid with any number of clues (i.e. cells that are already filled in), then the program will fill in the remaining cells using three separate algorithms. If no file is provided, the program will simply solve the test grids found in the directory. 

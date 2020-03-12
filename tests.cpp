//  Project Identifier: N/A
//              Author: Vishal Nayak
//             Project: Sudoku Solver
//              Module: tests.cpp
//         Description: Unit tests for Grid & Sudoku algorithms
//

#include <fstream>
#include <iostream>
#include <string>
#include "Grid.h"
#include "solver.h"

using namespace std;

const string PATHNAME = "/Users/vrnayak/Desktop/Coding/Personal/Sudoku Solver/Sudoku Grids/";

// Assert Functions
bool ASSERT_TRUE(bool statement) {
	
	if (statement) return true;
    else exit(3);
} // ASSERT_TRUE()

template <typename Type>
bool ASSERT_EQUAL(Type obj1, Type obj2) {
	
	if (obj1 == obj2) return true;
	else exit(7);
} // ASSERT_EQUAL()

// Testing Functions
void testCtor(Grid &sudokuGrid);
void testSet(Grid &sudokuGrid);
void testGet(Grid &sudokuGrid);
void testAt(Grid &sudokuGrid);
void testPrint(Grid &sudokuGrid);
void testCheckIfValid(Grid & sudokuGrid);
void testFindFirstEmptyCell(Grid &sudokuGrid);

int main() {
    
    Grid sudokuGrid;
	ifstream gridIn(PATHNAME + "grid1.txt");
	Grid sudokuGrid2(gridIn);
	testCtor(sudokuGrid);
    cout << "Default Ctor: PASS" << endl;
    
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            sudokuGrid.set(row, col, row);
        } // for...col
    } // for...row
    
	testSet(sudokuGrid);
    cout << "Set: PASS" << endl;
    
	testGet(sudokuGrid);
    cout << "Get: PASS" << endl;
	
	testAt(sudokuGrid);
	cout << "At: PASS" << endl;
	
	testCheckIfValid(sudokuGrid2);
	cout << "CheckIfValid: PASS" << endl;
	
	testFindFirstEmptyCell(sudokuGrid2);
	cout << "FindFirstEmptyCell: PASS" << endl;

	testPrint(sudokuGrid2);
	cout << "Print: PASS" << endl;
	
    return 0;
}

void testCtor(Grid &sudokuGrid) {
	
	for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            ASSERT_EQUAL(sudokuGrid.at(row, col), 0);
        } // for...col
    } // for...row
} // testCtor()

void testSet(Grid &sudokuGrid) {
	
	for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            ASSERT_EQUAL(sudokuGrid.at(row, col), row);
        } // for...col
    } // for...row
} // testSet()

void testGet(Grid &sudokuGrid) {
	
	ASSERT_EQUAL(sudokuGrid.getRow(0), 0);
	ASSERT_EQUAL(sudokuGrid.getCol(0), 0);
	ASSERT_EQUAL(sudokuGrid.getBox(0), 0);
	
	ASSERT_EQUAL(sudokuGrid.getRow(2), 0);
	ASSERT_EQUAL(sudokuGrid.getCol(2), 2);
	ASSERT_EQUAL(sudokuGrid.getBox(2), 0);

	ASSERT_EQUAL(sudokuGrid.getRow(22), 2);
	ASSERT_EQUAL(sudokuGrid.getCol(22), 4);
	ASSERT_EQUAL(sudokuGrid.getBox(22), 1);
    
	ASSERT_EQUAL(sudokuGrid.getRow(26), 2);
	ASSERT_EQUAL(sudokuGrid.getCol(26), 8);
	ASSERT_EQUAL(sudokuGrid.getBox(26), 2);
	
	ASSERT_EQUAL(sudokuGrid.getRow(37), 4);
	ASSERT_EQUAL(sudokuGrid.getCol(37), 1);
	ASSERT_EQUAL(sudokuGrid.getBox(37), 3);
	
	ASSERT_EQUAL(sudokuGrid.getRow(32), 3);
	ASSERT_EQUAL(sudokuGrid.getCol(32), 5);
	ASSERT_EQUAL(sudokuGrid.getBox(32), 4);
	
	ASSERT_EQUAL(sudokuGrid.getRow(80), 8);
	ASSERT_EQUAL(sudokuGrid.getCol(80), 8);
	ASSERT_EQUAL(sudokuGrid.getBox(80), 8);
	
	// getIndex()
	ASSERT_EQUAL(sudokuGrid.getIndex(0, 0), 0);
	ASSERT_EQUAL(sudokuGrid.getIndex(0, 2), 2);
	ASSERT_EQUAL(sudokuGrid.getIndex(2, 4), 22);
	ASSERT_EQUAL(sudokuGrid.getIndex(2, 8), 26);
	
	ASSERT_EQUAL(sudokuGrid.getIndex(4, 1), 37);
	ASSERT_EQUAL(sudokuGrid.getIndex(3, 5), 32);
	ASSERT_EQUAL(sudokuGrid.getIndex(5, 8), 53);
	ASSERT_EQUAL(sudokuGrid.getIndex(8, 8), 80);
} // testGet()

void testAt(Grid &sudokuGrid) {
	
	for (int row = 0; row < 9; ++row) {
		for (int col = 0; col < 9; ++col) {
			ASSERT_EQUAL(sudokuGrid.at(row, col), row);
		} // for...col
	} // for...row
} // testAt()

void testCheckIfValid(Grid &sudokuGrid) {
	
	for (int row = 0; row < 9; ++row) {
		for (int col = 0; col < 9; ++col) {
			
			int val = sudokuGrid.at(row, col);
			sudokuGrid.set(row, col, 0);
			
			for (int i = 1; i <= 9; ++i) {
				bool valid = sudokuGrid.checkIfValid(row, col, i);
				if (i == val) ASSERT_TRUE(valid);
				else ASSERT_TRUE(!valid);
			} // for...i
			sudokuGrid.set(row, col, val);
		} // for...col
	} // for...row
} // testCheckIfValid()

void testFindFirstEmptyCell(Grid &sudokuGrid) {
	
	for (int row = 0; row < 9; ++row) {
		for (int col = 0; col < 9; ++col) {
			
			int val = sudokuGrid.at(row, col);
			sudokuGrid.set(row, col, 0);
			ASSERT_EQUAL(sudokuGrid.findFirstEmptyCell(),
						 sudokuGrid.getIndex(row, col));
			sudokuGrid.set(row, col, val);
		} // for...col
	} // for...row
	ASSERT_EQUAL(sudokuGrid.findFirstEmptyCell(), -1);
} // testFindFirstEmptyCell()

void testPrint(Grid &sudokuGrid) { sudokuGrid.print(cout); }

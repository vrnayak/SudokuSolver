//  Project Identifier: 490395975692179385863
//              Author: Vishal Nayak
//             Project: Sudoku Solver
//              Module: driver.cpp
//         Description: Reads in Sudoku Grid
//

#include <cmath>
#include <ctime>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Grid.h"
#include "solver.h"

using namespace std;

const string IN = ".in";
const string OUT = ".out";
const string CORRECT = ".correct";
const string PATHNAME = "/Users/vrnayak/Desktop/Coding/Personal"
						"/Sudoku Solver/Sudoku Grids/grid";
const int NUM_GRIDS = 4;

void printInfo();
void printHelp();
bool ASSERT_TRUE(bool statement);
bool getOpts(int argc, char *argv[]);
bool fileComp(string fileName1, string fileName2);
void solve(Grid &sudokuGrid, string fileOut, string fileCorrect);
void solveInfo(Grid &sudokuGrid, string fileOut, string fileCorrect);

int main(int argc, char *argv[]) {
	
	bool info = getOpts(argc, argv);
	if (info) printInfo();
	for (int i = 1; i <= NUM_GRIDS; ++i) {
		
		string comment;
		string fileIn = PATHNAME + to_string(i) + IN;
		string fileOut = PATHNAME + to_string(i) + OUT;
		string fileCorrect = PATHNAME + to_string(i) + CORRECT;
		
		ifstream inputStream(fileIn);
		getline(inputStream, comment); // First line is a comment
		Grid sudokuGrid(inputStream);
		
		if (info) {
			cout << "Sudoku Grid #" << i << "\n";
			solveInfo(sudokuGrid, fileOut, fileCorrect);
		} else {
			solve(sudokuGrid, fileOut, fileCorrect);
		} // if..else
	} // for...i
	return 0;
} // main()

bool ASSERT_TRUE(bool statement) {
	
	if (statement) return true;
	else exit(3);
} // ASSERT_TRUE()

bool getOpts(int argc, char *argv[]) {
	
	opterr = true;
	bool info = false;
    int choice, optionIndex = 0;
    option longOpts[] = {{ "help", no_argument, nullptr, 'h' },
                         { "info", no_argument, nullptr, 'i' }};
    
    while ((choice = getopt_long(argc, argv, "hi", longOpts,
                                 &optionIndex)) != -1) {
        switch (choice) {
            case 'h':
				printHelp();
                break;
            
            case 'i':
                info = true;
                break;
                
            default:
                cerr << "Invalid command line flag." << endl;
                exit(1);
        } // switch...choice
    } // while...choice
	return info;
} // getOpts()

void printInfo() {
	
	cout << "Sudoku Solver Program\n"
		 << "# of Grids to Solve: " << NUM_GRIDS
		 << endl << endl;
} // printInfo()

void printHelp() {
	
	cout << "How To Use Sudoku Solver Program:\n"
		 << "./driver.exe [--help] [--info]\n"
		 << "--help flag provides informational message about use info\n"
		 << "--info flag is optional, it provides more details of how\n"
		 << "the sudoku grid was solved (e.g. times, methods)."
		 << endl;
	exit(0);
}

bool fileComp(string fileName1, string fileName2) {
	
	ifstream file1(fileName1), file2(fileName2);
	
	int cell1, cell2;
	vector<int> grid;
	grid.reserve(81);
	
	while (file1 >> cell1)
		grid.push_back(cell1);

	int counter = 0;
	while (file2 >> cell2) {
		if (grid[counter++] != cell2)
			return false;
	} // while
	return counter == 81;
} // fileComp()

void solve(Grid &sudokuGrid, string fileOut, string fileCorrect) {
	
	int emptyCells = 81;
	while (emptyCells > sudokuGrid.numEmptyCells()) {
		
		emptyCells = sudokuGrid.numEmptyCells();
		smartSolve(sudokuGrid);
		simpleSolve(sudokuGrid);
	} // while
	
	bruteForceSolve(sudokuGrid);
	ofstream os(fileOut);
	sudokuGrid.print(os);
	ASSERT_TRUE(fileComp(fileOut, fileCorrect));
} // solve()

void solveInfo(Grid &sudokuGrid, string fileOut, string fileCorrect) {
	
	clock_t start;
	double smartTime = 0.0, simpleTime = 0.0, forceTime = 0.0;
	int smartCells = 0, simpleCells = 0, forceCells = 0;
	int emptyCells = 81;
	
	cout << "# of Empty Cells: "
		 << sudokuGrid.numEmptyCells() << "\n";
	
	while (emptyCells > sudokuGrid.numEmptyCells()) {
		
		emptyCells = sudokuGrid.numEmptyCells();
		start = std::clock();
		smartSolve(sudokuGrid);
		smartTime = (std::clock() - start) / (double) CLOCKS_PER_SEC;
		smartCells += emptyCells - sudokuGrid.numEmptyCells();
		
		emptyCells = sudokuGrid.numEmptyCells();
		start = std::clock();
		simpleSolve(sudokuGrid);
		simpleTime = (std::clock() - start) / (double) CLOCKS_PER_SEC;
		simpleCells += emptyCells - sudokuGrid.numEmptyCells();
		
	} // while
	
	start = std::clock();
	bruteForceSolve(sudokuGrid);
	forceTime = (std::clock() - start) / (double) CLOCKS_PER_SEC;
	forceCells = emptyCells;
	
	ofstream os(fileOut);
	sudokuGrid.print(os);
	ASSERT_TRUE(fileComp(fileOut, fileCorrect));
	double totalTime = smartTime + simpleTime + forceTime;
	
	cout << "SmartSolve:\t Filled " << smartCells << " cells in "
		 << smartTime * pow(10, 6) << " microseconds\n"
		 << "SimpleSolve: Filled " << simpleCells << " cells in "
		 << simpleTime * pow(10, 6) << " microseconds\n"
		 << "Brute Force: Filled " << forceCells << " cells in "
		 << forceTime * pow(10, 6)<< " microseconds\n"
		 << "Total Time Taken: " << totalTime * pow(10, 6)
		 << " microseconds\n" << endl;
} // solve()

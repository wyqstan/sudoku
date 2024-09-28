#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <string>
#include <set>
using namespace std; 
class Grid {
public:
    static const int GRID_SIZE = 9;
    static const int BOX_SIZE = 3;
    
    Grid(const std::string& puzzle);
    std::vector<int> getRow(int row);
    std::vector<int> getColumn(int col);
    std::vector<int> getBox(int row, int col);
    void printGrid() const;
    std::vector<std::vector<int> > grid;
    void parse(const std::string& puzzle);
};

class Sudoku {
public:
    Sudoku(const std::string& puzzle);
    void getInference();
	set<int> getPossibleValues(int row, int col);
	bool backtrack();

    Grid grid;
};

#endif // SUDOKU_H


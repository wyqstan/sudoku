#include "sudoku.h"
#include <iostream>
#include <sstream>
#include <vector>
#include<set>
using namespace std;
// Grid类构造函数：解析字符串并初始化二维数组
Grid::Grid(const string& puzzle) {
    parse(puzzle);
}

// 解析字符串，并将其转换为9x9的二维数组
void Grid::parse(const std::string& puzzle) {
    grid.resize(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
    int idx = 0;
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j] = puzzle[idx++] - '0';
        }
    }
}

// 获取指定行的数字
std::vector<int> Grid::getRow(int row) {
    return grid[row];
}

// 获取指定列的数字
std::vector<int> Grid::getColumn(int col) {
    std::vector<int> column(GRID_SIZE);
    for (int i = 0; i < GRID_SIZE; ++i) {
        column[i] = grid[i][col];
    }
    return column;
}

// 获取指定宫的数字（3x3子矩阵）
std::vector<int> Grid::getBox(int row, int col) {
    std::vector<int> box;
    int startRow = (row / BOX_SIZE) * BOX_SIZE;
    int startCol = (col / BOX_SIZE) * BOX_SIZE;

    for (int i = startRow; i < startRow + BOX_SIZE; ++i) {
        for (int j = startCol; j < startCol + BOX_SIZE; ++j) {
            box.push_back(grid[i][j]);
        }
    }
    return box;
}

// 输出当前棋盘
void Grid::printGrid() const {
    for (int i=0; i<grid.size(); ++i) {
        for (int j=0;j<grid[0].size();++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Sudoku类构造函数
Sudoku::Sudoku(const std::string& puzzle) : grid(puzzle) {}

// 推理候选值（仅为雏形，推理规则需要进一步实现）
void Sudoku::getInference() {
        // 遍历整个棋盘，寻找未填充的空格
//    for (int row = 0; row < Grid::GRID_SIZE; ++row) {
//        for (int col = 0; col < Grid::GRID_SIZE; ++col) {
//            if (grid.getRow(row)[col] == 0) {  // 如果是空格
//                set<int> candidates = getPossibleValues(row, col);
//                
//                // 输出当前空格的候选值
//                cout << "候选值 (" << row << ", " << col << "): ";
//		    for (std::set<int>::iterator it = candidates.begin(); it != candidates.end(); ++it) {
//		        std::cout << *it << " ";
//		    }
//                cout << std::endl;
//            }
//        }
//    }
	if(backtrack()){
		cout<<"找到的解："<<endl;
		grid.printGrid();
	}
	else{
		cout<<"没有找到解。"<<endl;
	}
}

bool Sudoku::backtrack(){
        for (int row = 0; row < Grid::GRID_SIZE; ++row) {
            for (int col = 0; col < Grid::GRID_SIZE; ++col) {
                if (grid.getRow(row)[col] == 0) {  // 如果是空格
                    set<int> candidates = getPossibleValues(row, col);
                    for (std::set<int>::iterator it = candidates.begin(); it != candidates.end(); ++it) {
                        grid.grid[row][col] = *it;  // 填入候选值
                        if (backtrack()) {  // 递归尝试解决
                            return true;
                        }
                        grid.grid[row][col] = 0;  // 回溯时重置
                    }
                    return false;  // 找不到有效候选值
                }
            }
        }
        return true;  // 所有单元格已填充
}
// 获取某个空格的候选值
set<int> Sudoku::getPossibleValues(int row, int col) {
    std::set<int> possibleValues;
    for(int i=1;i<=9;++i){
    	possibleValues.insert(i);
	}
    
    // 获取当前行、列和宫
    std::vector<int> rowValues = grid.getRow(row);
    std::vector<int> colValues = grid.getColumn(col);
    std::vector<int> boxValues = grid.getBox(row, col);
    
    // 删除已经在当前行中的数字
    for (int i=0;i<rowValues.size();++i) {
        possibleValues.erase(rowValues[i]);
    }
    
    // 删除已经在当前列中的数字
    for (int i=0;i<colValues.size();++i) {
        possibleValues.erase(colValues[i]);
    }
    
    // 删除已经在当前3x3宫格中的数字
    for (int i=0;i<boxValues.size();++i) {
        possibleValues.erase(boxValues[i]);
    }
    
    return possibleValues;  // 返回剩下的可能值
}


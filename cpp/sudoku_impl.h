#include "sudoku.h"
#include <iostream>
#include <sstream>
#include <vector>
#include<set>
using namespace std;
// Grid�๹�캯���������ַ�������ʼ����ά����
Grid::Grid(const string& puzzle) {
    parse(puzzle);
}

// �����ַ�����������ת��Ϊ9x9�Ķ�ά����
void Grid::parse(const std::string& puzzle) {
    grid.resize(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
    int idx = 0;
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j] = puzzle[idx++] - '0';
        }
    }
}

// ��ȡָ���е�����
std::vector<int> Grid::getRow(int row) {
    return grid[row];
}

// ��ȡָ���е�����
std::vector<int> Grid::getColumn(int col) {
    std::vector<int> column(GRID_SIZE);
    for (int i = 0; i < GRID_SIZE; ++i) {
        column[i] = grid[i][col];
    }
    return column;
}

// ��ȡָ���������֣�3x3�Ӿ���
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

// �����ǰ����
void Grid::printGrid() const {
    for (int i=0; i<grid.size(); ++i) {
        for (int j=0;j<grid[0].size();++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Sudoku�๹�캯��
Sudoku::Sudoku(const std::string& puzzle) : grid(puzzle) {}

// �����ѡֵ����Ϊ���Σ����������Ҫ��һ��ʵ�֣�
void Sudoku::getInference() {
        // �����������̣�Ѱ��δ���Ŀո�
//    for (int row = 0; row < Grid::GRID_SIZE; ++row) {
//        for (int col = 0; col < Grid::GRID_SIZE; ++col) {
//            if (grid.getRow(row)[col] == 0) {  // ����ǿո�
//                set<int> candidates = getPossibleValues(row, col);
//                
//                // �����ǰ�ո�ĺ�ѡֵ
//                cout << "��ѡֵ (" << row << ", " << col << "): ";
//		    for (std::set<int>::iterator it = candidates.begin(); it != candidates.end(); ++it) {
//		        std::cout << *it << " ";
//		    }
//                cout << std::endl;
//            }
//        }
//    }
	if(backtrack()){
		cout<<"�ҵ��Ľ⣺"<<endl;
		grid.printGrid();
	}
	else{
		cout<<"û���ҵ��⡣"<<endl;
	}
}

bool Sudoku::backtrack(){
        for (int row = 0; row < Grid::GRID_SIZE; ++row) {
            for (int col = 0; col < Grid::GRID_SIZE; ++col) {
                if (grid.getRow(row)[col] == 0) {  // ����ǿո�
                    set<int> candidates = getPossibleValues(row, col);
                    for (std::set<int>::iterator it = candidates.begin(); it != candidates.end(); ++it) {
                        grid.grid[row][col] = *it;  // �����ѡֵ
                        if (backtrack()) {  // �ݹ鳢�Խ��
                            return true;
                        }
                        grid.grid[row][col] = 0;  // ����ʱ����
                    }
                    return false;  // �Ҳ�����Ч��ѡֵ
                }
            }
        }
        return true;  // ���е�Ԫ�������
}
// ��ȡĳ���ո�ĺ�ѡֵ
set<int> Sudoku::getPossibleValues(int row, int col) {
    std::set<int> possibleValues;
    for(int i=1;i<=9;++i){
    	possibleValues.insert(i);
	}
    
    // ��ȡ��ǰ�С��к͹�
    std::vector<int> rowValues = grid.getRow(row);
    std::vector<int> colValues = grid.getColumn(col);
    std::vector<int> boxValues = grid.getBox(row, col);
    
    // ɾ���Ѿ��ڵ�ǰ���е�����
    for (int i=0;i<rowValues.size();++i) {
        possibleValues.erase(rowValues[i]);
    }
    
    // ɾ���Ѿ��ڵ�ǰ���е�����
    for (int i=0;i<colValues.size();++i) {
        possibleValues.erase(colValues[i]);
    }
    
    // ɾ���Ѿ��ڵ�ǰ3x3�����е�����
    for (int i=0;i<boxValues.size();++i) {
        possibleValues.erase(boxValues[i]);
    }
    
    return possibleValues;  // ����ʣ�µĿ���ֵ
}


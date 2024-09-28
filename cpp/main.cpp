#include "sudoku_impl.h"
#include <iostream>
using namespace std;
int main() {
    string puzzle = "017903600000080000900000507072010430000402070064370250701000065000030000005601720";

    Sudoku sudoku(puzzle);
    
    std::cout << "³õÊ¼ÆåÅÌ:" << std::endl;
    sudoku.getInference();
    return 0;
}


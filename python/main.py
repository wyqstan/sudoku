from sudoku import Sudoku

if __name__ == "__main__":
    puzzle="017903600000080000900000507072010430000402070064370250701000065000030000005601720"
    sudoku=Sudoku(puzzle)
    print("初始棋盘:")
    sudoku.get_inference()
